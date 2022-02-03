#include "tests.h"
#include "masked.h"
#include "masked_utils.h"
#include "masked_representations.h"
#include "hal.h"
#include <stdio.h>
#include "poly.h"
#include "gadgets.h"

static void report_test(char *msg,int err){
    char buf[128];
    if(err==0){
        sprintf(buf,"%s -> OK",msg);
    }else{
        sprintf(buf,"%s -> /!\\ Error /!\\",msg);
    }
    hal_send_str(buf);
}
unsigned int test_function(){

    int err = 1;
    report_test("test_function",err);
    err = 0;
    report_test("test_function",err);
    return err;
}
unsigned int test_convertions_APoly(){
    poly x;
    StrAPoly strmasked_x,strmasked_y;
    APoly masked_x;

    masked_poly(strmasked_x,&x);
    StrAPoly2APoly(masked_x,strmasked_x);
    APoly2StrAPoly(strmasked_y,masked_x);

    int err = 0;
    for(int i=0;i<KYBER_N;i++){
        for(int d=0;d<NSHARES;d++){
            err += (strmasked_x[d][i] != strmasked_y[d][i]);
        }
    }

    report_test("test_convertions_APoly",err);
    return err;
}

unsigned int test_convertions_bitslice(){
    uint32_t bitslice[COEF_NBITS * NSHARES];
    int16_t dense_x[BSSIZE * NSHARES];
    int16_t dense_y[BSSIZE * NSHARES];
    
    for(int i=0;i<BSSIZE * NSHARES;i++){
        dense_x[i] = rand32() & ((1<<COEF_NBITS)-1);    
    }

    // map to bitslice
    masked_dense2bitslice(
            NSHARES,
            BSSIZE,
            COEF_NBITS,
            bitslice,NSHARES,1,
            dense_x,NSHARES,1);

    masked_bitslice2dense(
            NSHARES,
            BSSIZE,
            COEF_NBITS,
            dense_y,NSHARES,1,
            bitslice,NSHARES,1);

    int err = 0;
    for(int i=0;i<COEF_NBITS;i++){
        for(int d=0;d<NSHARES;d++){
            err += (dense_y[i*NSHARES + d] != dense_x[i*NSHARES + d]);
        }
    }

    report_test("test_convertions_bitslice",err);
    return err;
}

unsigned int test_xor_bitslice(){
    uint32_t masked_x[NSHARES],masked_y[NSHARES],masked_z[NSHARES];
    uint32_t x,y,z;
    int d;
    for(d=0;d<NSHARES;d++){
        masked_x[d] = rand32();
        masked_y[d] = rand32();
    }
    masked_xor(NSHARES,
               masked_z,1,
               masked_x,1,
               masked_y,1);

    x=0;y=0;z=0;
    for(d=0;d<NSHARES;d++){
        x ^= masked_x[d];
        y ^= masked_y[d];
        z ^= masked_z[d];
    }

    int err = (z != (x^y));
    report_test("test_xor_bitslice",err);
    return err;
    
}

unsigned int test_and_bitslice(){
    uint32_t masked_x[NSHARES],masked_y[NSHARES],masked_z[NSHARES];
    uint32_t x,y,z;
    int d;
    for(d=0;d<NSHARES;d++){
        masked_x[d] = rand32();
        masked_y[d] = rand32();
    }
    masked_and(NSHARES,
               masked_z,1,
               masked_x,1,
               masked_y,1);

    x=0;y=0;z=0;
    for(d=0;d<NSHARES;d++){
        x ^= masked_x[d];
        y ^= masked_y[d];
        z ^= masked_z[d];
    }

    int err = (z != (x&y));
    report_test("test_and_bitslice",err);
    return err;
}

/*
unsigned int test_secadd(){
    size_t kbits = 1;
    uint32_t in1[kbits*NSHARES];
    uint32_t in2[kbits*NSHARES];
    uint32_t out[kbits*NSHARES];
    
    int i,err;
    for(i=0;i<kbits*NSHARES;i++){
        in1[i] = rand32();
        in2[i] = rand32();
    }

    secadd(NSHARES, kbits,
            out,1,NSHARES,
            in1,1,NSHARES,
            in2,1,NSHARES);

    uint32_t *masked_out_ptr[kbits];
    uint32_t *masked_in1_ptr[kbits];
    uint32_t *masked_in2_ptr[kbits];
    
    int16_t coeffs_out[BSSIZE*NSHARES];
    int16_t coeffs_in1[BSSIZE*NSHARES];
    int16_t coeffs_in2[BSSIZE*NSHARES];
    int16_t *coeffs_out_ptr[BSSIZE];
    int16_t *coeffs_in1_ptr[BSSIZE];
    int16_t *coeffs_in2_ptr[BSSIZE];

    for(i=0;i<kbits;i++){
        masked_out_ptr[i] = &out[i*NSHARES];
        masked_in1_ptr[i] = &in1[i*NSHARES];
        masked_in2_ptr[i] = &in2[i*NSHARES];
    }
    for(i=0;i<BSSIZE;i++){
        coeffs_out_ptr[i] = &coeffs_out[i*NSHARES];
        coeffs_in1_ptr[i] = &coeffs_in1[i*NSHARES];
        coeffs_in2_ptr[i] = &coeffs_in2[i*NSHARES];
    }

    masked_bitslice2dense(masked_out_ptr,coeffs_out_ptr,
                            kbits,BSSIZE,NSHARES);
    masked_bitslice2dense(masked_in1_ptr,coeffs_in1_ptr,
                            kbits,BSSIZE,NSHARES);
    masked_bitslice2dense(masked_in2_ptr,coeffs_in2_ptr,
                            kbits,BSSIZE,NSHARES);

    err = 0;
    for(i=0;i<BSSIZE;i++){
        int16_t uin1,uin2,uout;
        uin1 = 0; uin2 = 0; uout = 0;
        for(d=0;d<NSHARES;d++){
            uin1 ^= coeffs_in1[i*NSHARES + d];
            uin2 ^= coeffs_in2[i*NSHARES + d];
            uout ^= coeffs_out[i*NSHARES + d];
        }
        err += ((uin1 + uin2)&((1<<kbits)-1) != uout);
    }

    report_test("test_secadd",err);
    return err;
}
*/
