#include "reb-host.h"
#include <zlib.h> 

const char *init_block =
    "REBOL [\n"
        "Title: {ZLIB extension}\n"
        "Comment: {just a VERY simple variant}\n"
        "Name: zlib-rxt\n"
        "Type: extension\n"
    "]\n"
    "export zlib-decompress:  command[src [binary!]]\n"
    "export zlib-compress:  command[src [binary!]]\n"
    "export bin-test: command [bin [binary!] level [integer!]]\n"
;

enum fmod_commands {
    CMD_zlibDecompress,
    CMD_zlibCompress,
    CMD_binTest,

};

RL_LIB *RL;


const char *RX_Init(int opts, RL_LIB *lib) {
    RL = lib;
    return init_block;
}

int RX_Call(int cmd, RXIFRM *frm, void *data) {
    REBSER *ser;
    char *srcData;
    u32 index, srcLen, length;
    int result;
    
    switch (cmd) {
        case CMD_zlibDecompress: { 

            ser     = RXA_SERIES(frm, 1);
            srcData = (char *)RL_SERIES(ser, RXI_SER_DATA) + RXA_INDEX(frm, 1);
            srcLen  = RL_SERIES(ser, RXI_SER_TAIL) - RXA_INDEX(frm, 1);

            uLongf destLen = 5 * srcLen; //not perfect, but could be enough for my purpose
            Bytef *dest = malloc(destLen); 

            result = uncompress(dest, &destLen, srcData, srcLen);
            
            if(result==Z_OK){
                REBSER *destSer = RL_MAKE_STRING(destLen,0);
                for (index = 0; index < destLen; index++) {
                    RL_SET_CHAR(destSer, index, dest[index]);
                }
                
                free(dest);
                RXA_SERIES(frm, 1) = destSer;
                RXA_TYPE(frm, 1)   = RXT_BINARY;
                RXA_INDEX(frm, 1)  = 0;
                return RXR_VALUE;
            } else {
                free(dest);
                return RXR_NONE;
            }
        }
        case CMD_zlibCompress: { 

            ser     = RXA_SERIES(frm, 1);
            srcData = (char *)RL_SERIES(ser, RXI_SER_DATA) + RXA_INDEX(frm, 1);
            srcLen  = RL_SERIES(ser, RXI_SER_TAIL) - RXA_INDEX(frm, 1);

            uLongf destLen = (srcLen < 1024)?1024:srcLen; //not perfect, but could be enough for my purpose
            Bytef *dest = malloc(destLen); 
            
            int level = (int)RXA_INT64(frm, 2);
                    
            result = compress2(dest, &destLen, srcData, srcLen, level);
            
            if(result==Z_OK){
                REBSER *destSer = RL_MAKE_STRING(destLen,0);
                for (index = 0; index < destLen; index++) {
                    RL_SET_CHAR(destSer, index, dest[index]);
                }
                
                free(dest);
                RXA_SERIES(frm, 1) = destSer;
                RXA_TYPE(frm, 1)   = RXT_BINARY;
                RXA_INDEX(frm, 1)  = 0;
                return RXR_VALUE;
            } else {
                free(dest);
                return RXR_NONE;
            }
        }
        case CMD_binTest: {
          
            ser = RXA_SERIES(frm, 1);
            RL_PRINT("RXI_SER_WIDE = %d\n", RL_SERIES(ser, RXI_SER_WIDE));  
            RL_PRINT("RXI_SER_SIZE = %d\n", RL_SERIES(ser, RXI_SER_SIZE));
            RL_PRINT("RXI_SER_LEFT = %d\n", RL_SERIES(ser, RXI_SER_LEFT));
            srcLen =  - RL_GET_STRING(ser, RXA_INDEX(frm, 1), (void **)&srcData);
            RL_PRINT("index = %d\n", RXA_INDEX(frm, 1));
            RL_PRINT("srcLen= %d\n", srcLen);
            return RXR_NONE;
        }
     }
}
