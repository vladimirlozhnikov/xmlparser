#include "stdafx.h"
#include "Parser.h"
#include <malloc.h>

//#pragma stack_cleanup on

void XMLParser::Initialize(XMLObject* _pXMLO)
{
	_pXMLO->state = PARSE_STATE_START; 
	_pXMLO->offset = 0;
	bIntoQuotes_ = false;
}

void XMLParser::Release(XMLObject* _pXMLO)
{
	if (_pXMLO->attr)
	{
		free(_pXMLO->attr);
		_pXMLO->attr = null;
	}

	int i = 0;
	for (i = 0; i < _pXMLO->numChildren; i++)
	{
		XMLObject* rps = &(((XMLObject*)_pXMLO->child)[i]);
		Release(rps);
	}
	_pXMLO->numChildren = 0;

	if (_pXMLO->child)
	{
		free(_pXMLO->child);
		_pXMLO->child = null;
	}

	if (lastTagName_)
	{
		free(lastTagName_);
		lastTagName_ = null;
	}
	
	if ( strCloseTagName_ )
	{
		free(strCloseTagName_);
		strCloseTagName_ = null;
	}
	
	if (strBeginTagName_)
	{
		free(strBeginTagName_);
		strBeginTagName_ = null;
	}
}

bool XMLParser::Parse(XMLObject* _pXMLO, const char* _pstrXmlDocument,
                      int _wEnd, int* _pwElementSize,
                      bool* _pwShortCircuit, int* _pwErr,
                      int* _pwErrOffset)
{
	lastTagName_ = (char*)malloc(512);
	memset(lastTagName_, 0, 512);
	strBeginTagName_ = (char*)malloc(512);
	memset(strBeginTagName_, 0, 512);
	strCloseTagName_ = (char*)malloc(512);
	memset(strCloseTagName_, 0, 512);

	return _ExtractXMLFragmentFromStream(_pXMLO, _pstrXmlDocument,
	                                     _wEnd, _pwElementSize,
	                                     _pwShortCircuit, _pwErr,
                                         _pwErrOffset);
}

char* XMLParser::GetElement(char* _pstrXmlDocument,
                            XMLObject* _pXMLO, int* _pwElementsize)
{
	*_pwElementsize = _pXMLO->element_end - _pXMLO->element_bgn + 1;
	return &_pstrXmlDocument[_pXMLO->element_bgn];
}

char* XMLParser::GetTagName(char* _pstrXmlDocument,
                            XMLObject* _pXMLO, int* _pwLen)
{
	*_pwLen = _pXMLO->elementname_end - _pXMLO->elementname_bgn + 1;
	
	return &_pstrXmlDocument[_pXMLO->elementname_bgn];
}

char* XMLParser::GetContent(char* _pstrXmlDocument,
                            XMLObject* _pXMLO,
                            int* _pwLen,
                            int* _pwNumEncodings)
{
	if (_pXMLO->numChildren > 0) return null;
	if (_pXMLO->isEmptyElement) return null;

	*_pwLen =  _pXMLO->endtag_bgn - _pXMLO->starttag_end - 1;
	if (*_pwLen == 0)
		return null;

	*_pwNumEncodings = _pXMLO->numEncodings;

	return &_pstrXmlDocument[_pXMLO->starttag_end + 1];
}

XMLObject* XMLParser::GetChild(char* _pstrXmlDocument,
                               char* _pstrChild,
                               XMLObject* _pXMLO)
{
	int i = 0;
	int len = strlen(_pstrChild);

	for (i = 0; i < _pXMLO->numChildren; i++)
	{
		XMLObject *rps = &(((XMLObject*)_pXMLO->child)[i]);
		if (strncmp(&_pstrXmlDocument[rps->elementname_bgn],
		                 _pstrChild, len) == 0)
			return rps;
	} 

	return null; 
}

int XMLParser::GetNumChildren(XMLObject* _pXMLO)
{
	return _pXMLO->numChildren;
}

XMLObject* XMLParser::GetChild(XMLObject* _pXMLO,
                               int _n)
{
	if (_n >= _pXMLO->numChildren) return null;

	XMLObject* rps = &(((XMLObject*)(_pXMLO->child))[_n]);

	return rps;
}

char* XMLParser::GetAttributeByIndex(char* _pstrXmlDocument,
                                     XMLObject* _pXMLO,
                                     int _wIndex,
                                     int* _pwLen )
{
	if (_wIndex >= _pXMLO->numAttrs) return null;

	*_pwLen = _pXMLO->attr[_wIndex].name_end - _pXMLO->attr[_wIndex].name_start + 1;

	return &_pstrXmlDocument[_pXMLO->attr[_wIndex].name_start];
}

char* XMLParser::GetAttribute(char* _pstrXmlDocument,
                              char* _pstrAttribute,
                              XMLObject* _pXMLO,
                              int* _pwLen)
{
	int i = 0;
	int attrlen = strlen(_pstrAttribute);

	for (i = 0; i < _pXMLO->numAttrs; i++)
	{
		if (strncmp(&_pstrXmlDocument[_pXMLO->attr[i].name_start],
		                  _pstrAttribute, attrlen) == 0)
		{
			*_pwLen = _pXMLO->attr[i].value_end - 
				      _pXMLO->attr[i].value_start - 1;

			return &_pstrXmlDocument[_pXMLO->attr[i].value_start + 1];
		}
	}

	return null;
}

bool XMLParser::_ExtractXMLFragmentFromStream(XMLObject* _pXMLO,
                                              const char* _pstrXmlDocument,
                                              int _wLen, 
	                                          int* _pwConsume,
	                                          bool* _pbStopAtStartTag,
	                                          int* _pwErr,
	                                          int* _pwErrOffset)
{
	while (true)
	{
		if (_pXMLO->offset == (_wLen + 1))
		{
			*_pwConsume = 0;
			return true;
		}	

		switch (_pXMLO->state)
		{
		case PARSE_STATE_START:
		{
			_pXMLO->numChildren = 0;
			_pXMLO->child = null;
			_pXMLO->attr = null;
			_pXMLO->state = PARSE_STATE_SKIP_WHITE_SPACE;
			_pXMLO->element_bgn = _pXMLO->offset;
			_pXMLO->element_end = _pXMLO->offset;
			_pXMLO->isEmptyElement = false;
			_pXMLO->start = _pXMLO->offset;
			_pXMLO->numEncodings = 0;
			_pXMLO->numLevel = 1;
												
			continue;
		}
		case PARSE_STATE_SKIP_WHITE_SPACE:
		{
			if (IS_WHITE_SPACE(_pstrXmlDocument[_pXMLO->offset]))
			{
				goto INC_OFFSET;
			}
			else
			{
				_pXMLO->state = PARSE_STATE_CONFIRM_ANGLE_BRACKET_BGN;
				continue;
			}
		}
		case PARSE_STATE_CONFIRM_ANGLE_BRACKET_BGN:
		{
			if (_pstrXmlDocument[_pXMLO->offset] == '<')
			{
				_pXMLO->state = PARSE_STATE_CHECK_FOR_PROCESSING_INSTRUCTION;
				_pXMLO->starttag_bgn = _pXMLO->offset;
				_pXMLO->element_bgn = _pXMLO->offset;
				_pXMLO->numAttrs = 0;
						
				goto INC_OFFSET;
			}
			else
			{
				*_pwErr = PARSE_ERR_MISSING_ANGLE_BRACKET_BGN;
				*_pwErrOffset = _pXMLO->offset;

				return false;
			}
		}
		case PARSE_STATE_CHECK_FOR_PROCESSING_INSTRUCTION:
		{
			if (_pstrXmlDocument[_pXMLO->offset] == '?')
			{
				_pXMLO->state = PARSE_STATE_SKIP_TO_END_OF_PROCESSING_INSTRUCTION;

				goto INC_OFFSET;
			}
			else
			{
				_pXMLO->state = PARSE_STATE_ELEMENT_NAME_START;

				continue;	
			}
		}
		case PARSE_STATE_SKIP_TO_END_OF_PROCESSING_INSTRUCTION:
		{
			if (_pstrXmlDocument[_pXMLO->offset] == '>')
			{
				if (_pstrXmlDocument[_pXMLO->offset - 1] == '?')
				{
					_pXMLO->state = PARSE_STATE_GOT_PROCESSING_INSTRUCTION;
					_pXMLO->element_end = _pXMLO->offset;

					continue;
				}
				else
				{
					*_pwErr = PARSE_ERR_PI_IMPROPERLY_TERMINATED;
					*_pwErrOffset = _pXMLO->offset - 1;

					return false;
				}
			}
			else
				goto INC_OFFSET;
		}
		case PARSE_STATE_ELEMENT_NAME_START:
		{
			if (IS_WHITE_SPACE(_pstrXmlDocument[_pXMLO->offset]))
			{
				*_pwErr = PARSE_ERR_INVALID_WHITE_SPACE_IN_START_TAG;
				*_pwErrOffset = _pXMLO->offset;

				return false;
			}	
			else
			{
				_pXMLO->state = PARSE_STATE_ELEMENT_GET_NAME;
				_pXMLO->elementname_bgn = _pXMLO->offset;
				
				goto INC_OFFSET;
			}
		}
		case PARSE_STATE_ELEMENT_GET_NAME:
		{
			if (IS_WHITE_SPACE(_pstrXmlDocument[_pXMLO->offset]))
			{
				_pXMLO->elementname_end = _pXMLO->offset-1;
				_pXMLO->state = PARSE_STATE_SKIP_TO_END_OF_START_TAG;
				
				continue;
			}
			else if (_pstrXmlDocument[_pXMLO->offset] == '>')
			{ 
				if (_pstrXmlDocument[_pXMLO->elementname_bgn] == '/')
				{
					*_pwConsume = _pXMLO->offset - _pXMLO->start + 1;
					*_pwErrOffset = _pXMLO->elementname_bgn;
					*_pwErr = PARSE_ERR_END_TAG_IS_START_TAG;
					_pXMLO->elementname_bgn++;

					return false;
				}
				else if (_pstrXmlDocument[_pXMLO->offset - 1] == '/')
				{
					_pXMLO->element_end = _pXMLO->offset;
					_pXMLO->starttag_end = _pXMLO->offset;
					_pXMLO->elementname_end = _pXMLO->offset-2;
					_pXMLO->state = PARSE_STATE_GOT_EMPTY_ELEMENT;
					
					continue;
				}
				else
				{
					if (*_pbStopAtStartTag)
					{
						_pXMLO->starttag_end = _pXMLO->offset;
						_pXMLO->state = PARSE_STATE_SHORT_CIRCUIT_START_TAG;
						continue;
					}	
					else
					{
						_pXMLO->starttag_end = _pXMLO->offset;
						_pXMLO->state = PARSE_STATE_SKIP_TO_BGN_OF_END_TAG;

						goto INC_OFFSET;
					}
				}
			}
			else
			{
				_pXMLO->elementname_end = _pXMLO->offset;
			}

			goto INC_OFFSET;
		}
		case PARSE_STATE_SKIP_TO_END_OF_START_TAG:
		{
			if (_pstrXmlDocument[_pXMLO->offset] == '>')
			{
				if (_pstrXmlDocument[_pXMLO->offset - 1] == '/')
				{
					_pXMLO->state = PARSE_STATE_GOT_EMPTY_ELEMENT;
					_pXMLO->starttag_end = _pXMLO->element_end = _pXMLO->offset;
										
					continue;
				}
				else
				{	
					if (*_pbStopAtStartTag)
					{
						_pXMLO->starttag_end = _pXMLO->element_end = _pXMLO->offset;
						_pXMLO->state = PARSE_STATE_SHORT_CIRCUIT_START_TAG;

						continue;
					}
					else
					{
						_pXMLO->starttag_end = _pXMLO->element_end = _pXMLO->offset;
						_pXMLO->state = PARSE_STATE_SKIP_TO_BGN_OF_END_TAG;

						goto INC_OFFSET;
					}
				}
			}
			else if (_pstrXmlDocument[_pXMLO->offset] == '=')
			{
				_pXMLO->numAttrs++;

				goto INC_OFFSET;
			}
			else	
				goto INC_OFFSET;
		}
		case PARSE_STATE_SHORT_CIRCUIT_START_TAG:
		{
			if (*_pbStopAtStartTag)
			{
				*_pwConsume = _pXMLO->offset - _pXMLO->start + 1;

				return true;
			}
			else
			{
				_pXMLO->state = PARSE_STATE_SKIP_TO_BGN_OF_END_TAG;

				continue;
			}
		}
		case PARSE_STATE_SKIP_TO_BGN_OF_END_TAG:
		{
			if (_pstrXmlDocument[_pXMLO->offset] == '<')
			{
				_pXMLO->endtag_bgn = _pXMLO->offset;
				_pXMLO->state = PARSE_STATE_CONFIRM_END_TAG_BGN_SLASH;
				
				goto INC_OFFSET;
			}
			else if (_pstrXmlDocument[_pXMLO->offset] == '&')
			{
				_pXMLO->numEncodings++;

				goto INC_OFFSET;
			}
			else if (_pstrXmlDocument[_pXMLO->offset] == '\"')
			{
				 bIntoQuotes_ = !bIntoQuotes_;
		 
				 goto INC_OFFSET;
			}
			else if (_pstrXmlDocument[_pXMLO->offset] == '/' && !bIntoQuotes_)
			{
				if (_pstrXmlDocument[_pXMLO->offset + 1] == '>')
				{
					char* strLastTagName = lastTagName_;
					len1_ = 0;
					len1_ = _pXMLO->elementname_end - _pXMLO->elementname_bgn + 1;

					memset(strBeginTagName_, 0, len1_);
					memmove(strBeginTagName_, &_pstrXmlDocument[_pXMLO->elementname_bgn],
                    	    len1_);

					if (strncmp(strLastTagName, strBeginTagName_, len1_) == 0)
						_pXMLO->numLevel--;
                            
					goto INC_OFFSET;
				}
				else
				{
					goto INC_OFFSET;
				}
			}
			else
			{
				goto INC_OFFSET;
			}
		}
		case PARSE_STATE_CONFIRM_END_TAG_BGN_SLASH:
		{
			if (_pstrXmlDocument[_pXMLO->offset] != '/')
			{
				len1_ = 0;
				len1_ = _pXMLO->elementname_end - _pXMLO->elementname_bgn + 1;

			    memset(strBeginTagName_, 0, len1_);
			    memmove(strBeginTagName_, &_pstrXmlDocument[_pXMLO->elementname_bgn],
			            len1_);
			    memset(strCloseTagName_, 0, len1_);
			    memmove(strCloseTagName_, &_pstrXmlDocument[_pXMLO->offset], len1_);

				if (strncmp(strBeginTagName_, strCloseTagName_, len1_) == 0)
					_pXMLO->numLevel++;

				_pXMLO->state= PARSE_STATE_SKIP_TO_BGN_OF_END_TAG;
				memset(lastTagName_, 0, len1_);
				memmove(lastTagName_, strCloseTagName_, len1_);

				goto INC_OFFSET;
			}
			else
			{
				len1_ = 0;
				len1_ = _pXMLO->elementname_end - _pXMLO->elementname_bgn + 1;

			    memset(strBeginTagName_, 0, len1_);
                memmove(strBeginTagName_, &_pstrXmlDocument[_pXMLO->elementname_bgn],
                        len1_);

			    memset(strCloseTagName_, 0, len1_);
                memmove(strCloseTagName_, &_pstrXmlDocument[_pXMLO->offset + 1],
                        len1_);

				if (strncmp(strBeginTagName_, strCloseTagName_, len1_) == 0)
					_pXMLO->numLevel--;

				_pXMLO->state = PARSE_STATE_CONFIRM_END_TAG_BGN;

				goto INC_OFFSET;
			}
		}
		case PARSE_STATE_CONFIRM_END_TAG_BGN:
		{
			if (IS_WHITE_SPACE(_pstrXmlDocument[_pXMLO->offset]))
			{
				*_pwErr = PARSE_ERR_INVALID_WHITE_SPACE_IN_END_TAG;
				*_pwErrOffset = _pXMLO->offset;

				return false;
			}
			else
			{
				_pXMLO->state = PARSE_STATE_GET_END_TAG_NAME;
				_pXMLO->endtagname_bgn = _pXMLO->offset;

				goto INC_OFFSET;
			}
		}
		case PARSE_STATE_GET_END_TAG_NAME:
		{
			if (_pstrXmlDocument[_pXMLO->offset] == '>')
			{
				_pXMLO->state = PARSE_STATE_CONFIRM_ELEMENT;
				_pXMLO->endtag_end = _pXMLO->offset;
				_pXMLO->element_end = _pXMLO->offset;
			
				continue;
			}
			else
			{
				_pXMLO->endtagname_end = _pXMLO->offset;
				
				goto INC_OFFSET;
			}
		}
		case PARSE_STATE_CONFIRM_ELEMENT:
		{
			elementname_len_ = _pXMLO->elementname_end - _pXMLO->elementname_bgn + 1;
			if (elementname_len_ !=
				(_pXMLO->endtagname_end - _pXMLO->endtagname_bgn + 1))
			{
				_pXMLO->state = PARSE_STATE_SKIP_TO_BGN_OF_END_TAG;

				goto INC_OFFSET;
			}

			int index = 0;
			bool match = true;

			while (index < elementname_len_)
			{
				if (_pstrXmlDocument[_pXMLO->elementname_bgn + index] !=
					_pstrXmlDocument[_pXMLO->endtagname_bgn + index])
				{
					match = false;

					break;
				}

				index++;
			}
			if (_pXMLO->numLevel <= 0)
			{
				match = 1;
				_pXMLO->numLevel = 0;
			}
			else
			{
				match = 0;
			}
			if (!match)
			{
				_pXMLO->state = PARSE_STATE_SKIP_TO_BGN_OF_END_TAG;

				continue;
			}
			else
			{
				_pXMLO->state = PARSE_STATE_GOT_ELEMENT;

				continue;
			} 
		}
		case PARSE_STATE_GOT_PROCESSING_INSTRUCTION:
		{
			*_pwConsume = _pXMLO->offset - _pXMLO->start + 1;

			return true;
		}
		case PARSE_STATE_GOT_EMPTY_ELEMENT:
		{
			_pXMLO->element_end = _pXMLO->offset;
			_pXMLO->numChildren = 0;
			_pXMLO->attr = null;
			_pXMLO->child = null;
			_pXMLO->isEmptyElement = true;
			int numAttrs = 0;

			if (_pXMLO->numAttrs)
			{ 
				if (!_ExtractAttributes(_pstrXmlDocument, _pXMLO,
				                        &numAttrs, _pwErr, _pwErrOffset))
				{
					return false;
				}
			}

			_pXMLO->numAttrs = numAttrs;
			*_pwConsume = _pXMLO->offset - _pXMLO->start + 1;

			return true; 
		}
		case PARSE_STATE_GOT_ELEMENT:
		{
			_pXMLO->attr = null;
			int numAttrs = 0;

			if (_pXMLO->numAttrs)
			{ 
				if (!_ExtractAttributes(_pstrXmlDocument, _pXMLO,
				                        &numAttrs, _pwErr, _pwErrOffset))
				{
					return false;
				}
			}

			_pXMLO->numAttrs = numAttrs;
			_pXMLO->child = null;
			_pXMLO->numChildren = 0; 

			if (_pXMLO->starttag_end + 1 != _pXMLO->endtag_bgn)
			{
				XMLObject rps;
				rps.state = PARSE_STATE_START;
				rps.offset = _pXMLO->starttag_end + 1;
				int end = _pXMLO->endtag_bgn - 1;
				
				_pXMLO->numLevel = 0;

				while (true)
				{
					int cons = 0;
					bool stopAtStartTag = false;
					int err, errOffset;

					if (!_ExtractXMLFragmentFromStream(&rps,
					                                   _pstrXmlDocument,
					                                   end, &cons, 
						                               &stopAtStartTag,
 						                               &err, &errOffset))
					{
						break;
					}
					else if (cons == 0)
					{
						if (pCallback_ != null)
						{
							pCallback_->ElementParsed((XMLObject*)_pXMLO);
						}

						break;
					}
					else
					{
						_pXMLO->numEncodings = 0;
						_pXMLO->numChildren++;

						if (_pXMLO->child == null)
						{
							_pXMLO->child = malloc(sizeof(XMLObject));
							memmove(_pXMLO->child, (void*)&rps, sizeof(XMLObject));
						}
						else
						{
							void* child = null;
							child = malloc((unsigned int)(_pXMLO->numChildren * sizeof(XMLObject)));
							memmove(child, _pXMLO->child, ((_pXMLO->numChildren - 1) * sizeof(XMLObject)));
							free(_pXMLO->child);
							_pXMLO->child = child; 
			
							memmove(&(((XMLObject*)_pXMLO->child)[_pXMLO->numChildren - 1]),
							  	    (void*)&rps, sizeof(XMLObject));
						}
					}

					rps.state = PARSE_STATE_START;
					rps.offset ++;
															
					if (rps.offset >= end)
					{
						break;
					}
				}
			}

			*_pwConsume = _pXMLO->offset - _pXMLO->start + 1;
			*_pbStopAtStartTag = false;

			/*if( m_pCallback != null )
			{
				m_pCallback->ElementParsed( ( XMLObject* )_pXMLO );
			}*/

			return true;
		}
		default:

			break;
		}

	INC_OFFSET:
		_pXMLO->offset++;

		continue;
	}

	return false;
} 


bool XMLParser::_ExtractAttributes(const char* _pstrXmlDocument,
                                   XMLObject* _pXMLO,
                                   int* _pwNumAttrs,
                                   int* _pwErr,
                                   int* _pwErrOffset)
{
	int state = ATTR_START;
	int offset = _pXMLO->elementname_end + 1;
	char quote;
	*_pwNumAttrs = 0;

	if (_pXMLO->numAttrs == 0) return true;
	_pXMLO->attr = (_AttrType*)malloc(sizeof(_AttrType) * _pXMLO->numAttrs);

	while (true)
	{
		switch (state)
		{
			case ATTR_START:
			{
				if (IS_WHITE_SPACE(_pstrXmlDocument[offset]))
				{
					state = ATTR_SKIP_WHITE_SPACE;

					continue;
				}
				else 
				{
					state = ATTR_DONE_WHITE_SPACE;

					continue;
				}
			}
			case ATTR_SKIP_WHITE_SPACE:
			{
				if (IS_WHITE_SPACE(_pstrXmlDocument[offset]))
				{
					goto INCREMENT;
				}
				else
				{
					state = ATTR_DONE_WHITE_SPACE;

					continue;
				}
			}
			case ATTR_DONE_WHITE_SPACE:
			{
				if (_pstrXmlDocument[offset] == '>')
				{
					return true;
				}
				else if ((_pstrXmlDocument[offset] == '/') && (offset + 1) == _pXMLO->starttag_end)
				{
					return true;
				}
				else
				{
					state = ATTR_GET_NAME;
					_pXMLO->attr[*_pwNumAttrs].name_start = offset;
					_pXMLO->attr[*_pwNumAttrs].name_end = offset;

					continue;
				}
			}
			case ATTR_GET_NAME:
			{
				if (_pstrXmlDocument[offset] == '=')
				{
					state = ATTR_GET_QUOTE;
					_pXMLO->attr[*_pwNumAttrs].value_start = offset + 1;
					_pXMLO->attr[*_pwNumAttrs].value_end = offset + 1;

					goto INCREMENT;
				}
				else
				{
					_pXMLO->attr[*_pwNumAttrs].name_end = offset;

					goto INCREMENT;
				}
			}
			case ATTR_GET_QUOTE:
			{
				if (_pstrXmlDocument[offset] == '"')
				{
					quote = '"';
					state = ATTR_GET_VALUE;

					goto INCREMENT;
				}
				else if (_pstrXmlDocument[offset] == '\'')
				{
					quote = '\'';
					state = ATTR_GET_VALUE;

					goto INCREMENT;
				}
				else
				{
					*_pwErr = PARSE_ERR_MISSING_QUOTE_IN_ATTRIBUTE_VALUE;
					*_pwErrOffset = offset;

					return false;
				}
			}
			case ATTR_GET_VALUE:
			{
				if (_pstrXmlDocument[offset] == quote)
				{
					_pXMLO->attr[*_pwNumAttrs].value_end = offset;
					state = ATTR_START;
					(*_pwNumAttrs)++;

					goto INCREMENT;
				}
				else
				{
					_pXMLO->attr[*_pwNumAttrs].value_end = offset;

					goto INCREMENT;
				}
			}
			default: ;
		}

	INCREMENT:
		offset++;
		if (offset > _pXMLO->starttag_end)
		{
			*_pwErr = PARSE_ERR_TERMINATION_EXPECTED_IN_ATTR_LIST;
			*_pwErrOffset = offset;

			return false;
		}
	}

	return false;
}
