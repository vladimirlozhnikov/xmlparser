#ifndef __XML_DOCUMENTPARAMETERS_H__
#define __XML_DOCUMENTPARAMETERS_H__

#define PARSE_ERR_MISSING_ANGLE_BRACKET_BGN				10
#define PARSE_ERR_PI_IMPROPERLY_TERMINATED				20
#define PARSE_ERR_INVALID_WHITE_SPACE_IN_START_TAG		30
#define PARSE_ERR_INVALID_WHITE_SPACE_IN_END_TAG		40
#define PARSE_ERR_MISSING_QUOTE_IN_ATTRIBUTE_VALUE		50
#define PARSE_ERR_TERMINATION_EXPECTED_IN_ATTR_LIST		60
#define PARSE_ERR_UNEXPECTED_FORWARD_SLASH				70
#define PARSE_ERR_END_TAG_IS_START_TAG					80

#define ATTR_START				0
#define ATTR_SKIP_WHITE_SPACE	10
#define ATTR_DONE_WHITE_SPACE	11
#define ATTR_GET_NAME			20
#define ATTR_GET_QUOTE			30
#define ATTR_GET_VALUE			50

#define PARSE_STATE_START									0
#define PARSE_STATE_SKIP_WHITE_SPACE						5
#define PARSE_STATE_CONFIRM_ANGLE_BRACKET_BGN 				10

#define PARSE_STATE_CHECK_FOR_PROCESSING_INSTRUCTION		30
#define PARSE_STATE_SKIP_TO_END_OF_PROCESSING_INSTRUCTION	31
#define PARSE_STATE_GOT_PROCESSING_INSTRUCTION				32

#define PARSE_STATE_ELEMENT_NAME_START						40
#define PARSE_STATE_ELEMENT_GET_NAME						41
#define PARSE_STATE_SKIP_TO_END_OF_START_TAG				42

#define PARSE_STATE_SKIP_TO_BGN_OF_END_TAG					50
#define PARSE_STATE_CONFIRM_END_TAG_BGN_SLASH				51
#define PARSE_STATE_CONFIRM_END_TAG_BGN						52
#define PARSE_STATE_GET_END_TAG_NAME						53
#define PARSE_STATE_CONFIRM_ELEMENT							54

#define PARSE_STATE_SHORT_CIRCUIT_START_TAG					60
#define PARSE_STATE_GOT_EMPTY_ELEMENT						61
#define PARSE_STATE_GOT_ELEMENT								62

#define IS_WHITE_SPACE(x)  ((x==0x20)||(x==0x0D)||(x==0x0A)||(x==0x09))

typedef struct
{
	int name_start;
	int name_end;
	int value_start;
	int value_end;
}_AttrType;

typedef struct

{
	int offset;
	int start;
	int element_bgn;
	int element_end;
	int starttag_bgn;
	int starttag_end;
	int elementname_bgn;
	int elementname_end;
	int endtag_bgn;
	int endtag_end;
	int endtagname_bgn;
	int endtagname_end;
	int numAttrs;
	int numChildren;
	unsigned char state;
	bool isEmptyElement;
	int numEncodings;
	int numLevel;
	_AttrType* attr;
	void* child;
}XMLObject;

#endif 