#include "reb-host.h"
#include "../include/demo-ext.h"

#ifdef TO_WIN32
#include "../include/helpers.h"
#endif

const char *init_block =
	"REBOL [\n"
		"Title: {REBOL Extension demo}\n"
		"Name: demo-ext\n"
		"Type: extension\n"
	"]\n"
	"words: [unset! none! handle! logic! integer! decimal! percent! char! pair! tuple! time! date! word! set-word! get-word! lit-word! refinement! issue! string! file! email! url! tag! block! paren! path! set-path! get-path! lit-path! binary! bitset! vector! image! gob! object! module! some-word]\n"
	"init-words: command [words [block!]]\n"
    "init-words words\n"
	"export hello-test: command [{Prints hello from a REBOL extension.}]\n"
	"export return-type-test: command [\n"
        "{Returns requested datatype.}\n"
        "type [word!]\n"
	"]\n"
;

RL_LIB *RL;
static u32* demo_ext_words;

RXIEXT const char *RX_Init(int opts, RL_LIB *lib) {
	RL = lib;
	if (!CHECK_STRUCT_ALIGN) return 0;
	return init_block;
}

RXIEXT int RX_Quit(int opts) {
	return 0;
}

RXIEXT int RX_Call(int cmd, RXIFRM *frm, void *data) {
	switch (cmd) {
	    case CMD_DEMO_INIT_WORDS:
            demo_ext_words = RL_MAP_WORDS(RXA_SERIES(frm,1));
            break;

        case CMD_DEMO_HELLO_TEST:
            RL_PRINT((REBYTE*)"%s\n", "Hello from REBOL extension!");
            break;

        case CMD_DEMO_TYPE_TEST:
            switch (RL_FIND_WORD(demo_ext_words,RXA_WORD(frm, 1))){
                case W_DEMO_INTEGER:
                    RXA_INT64(frm, 1) = 1234;
                    RXA_TYPE(frm, 1) = RXT_INTEGER;
                    return RXR_VALUE;

                case W_DEMO_DECIMAL:
                    RXA_DEC64(frm, 1) = 12.34;
                    RXA_TYPE(frm, 1) = RXT_DECIMAL;
                    return RXR_VALUE;

                case W_DEMO_CHAR:
                    RXA_CHAR(frm, 1) = 'c';
                    RXA_TYPE(frm, 1) = RXT_CHAR;
                    return RXR_VALUE;
#ifdef TO_WIN32
                case W_DEMO_STRING:
                    {
                        RXA_SERIES(frm, 1) = MultiByteToRebser("Hello world! UTF8 chars: ěščřžýáíé");
                        RXA_TYPE(frm, 1) = RXT_STRING;
                        return RXR_VALUE;
                    }
#endif
                case W_DEMO_LOGIC:
                    RXA_LOGIC(frm, 1) = TRUE;
                    RXA_TYPE(frm, 1) = RXT_LOGIC;
                    return RXR_VALUE;

                case W_DEMO_PAIR:
                    RXA_PAIR(frm, 1).x = 12.34;
                    RXA_PAIR(frm, 1).y = 56.78;
                    RXA_TYPE(frm, 1) = RXT_PAIR;
                    return RXR_VALUE;

                case W_DEMO_PERCENT:
                    RXA_DEC64(frm, 1) = 0.1234;
                    RXA_TYPE(frm, 1) = RXT_PERCENT;
                    return RXR_VALUE;

                case W_DEMO_TUPLE:
                    {
                        REBYTE* t = RXA_TUPLE(frm, 1);
                        t[0]=7; //tuple size (max 7)
                        t[1]=1;
                        t[2]=2;
                        t[3]=3;
                        t[4]=4;
                        t[5]=5;
                        t[6]=6;
                        t[7]=7;
                        RXA_TYPE(frm, 1) = RXT_TUPLE;
                        return RXR_VALUE;
                    }

                case W_DEMO_TIME:
                    RXA_TIME(frm, 1) = ((17 * 3600) + (15 * 60) + 25.123) * 1e9; //17:15:25.123
                    RXA_TYPE(frm, 1) = RXT_TIME;
                    return RXR_VALUE;

                case W_DEMO_WORD:
                    RXA_WORD(frm, 1) = demo_ext_words[W_DEMO_SOME_WORD];
                    RXA_TYPE(frm, 1) = RXT_WORD;
                    return RXR_VALUE;

                case W_DEMO_NONE:
                    RXA_TYPE(frm, 1) = RXT_NONE;
                    return RXR_VALUE;

                case W_DEMO_UNSET:
                    RXA_TYPE(frm, 1) = RXT_UNSET;
                    return RXR_VALUE;

            }
            break;

        default:
            return RXR_NO_COMMAND;
	}
	return RXR_UNSET;
}
