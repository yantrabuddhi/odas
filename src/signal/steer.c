    
    #include "steer.h"

    steers_obj * steers_construct_zero(const unsigned int halfFrameSize, const unsigned int nSeps, const unsigned int nChannels) {

        steers_obj * obj;
        unsigned int iSep;

        obj = (steers_obj *) malloc(sizeof(steers_obj));
        
        obj->nSeps = nSeps;
        obj->nChannels = nChannels;
        obj->halfFrameSize = halfFrameSize;

        obj->array = (float **) malloc(sizeof(float *) * obj->nSeps);
        
        for (iSep = 0; iSep < obj->nSeps; iSep++) {

            obj->array[iSep] = (float *) malloc(sizeof(float) * obj->halfFrameSize * obj->nChannels * 2);
            memset(obj->array[iSep], 0x00, sizeof(float) * obj->halfFrameSize * obj->nChannels * 2);

        }

        return obj;

    }

    void steers_destroy(steers_obj * obj) {

        unsigned int iSep;

        for (iSep = 0; iSep < obj->nSeps; iSep++) {

            free((void *) obj->array[iSep]);

        }

        free((void *) obj->array);
        free((void *) obj);

    }

    void steers_copy(steers_obj * dest, const steers_obj * src) {

        unsigned int iSep;

        for (iSep = 0; iSep < src->nSeps; iSep++) {
            memcpy(dest->array[iSep], src->array[iSep], src->halfFrameSize * src->nChannels * 2 * sizeof(float));
        }        

    }

    void steers_printf(const steers_obj * obj) {

        unsigned int iBin;
        unsigned int iSep;
        unsigned int iChannel;

        float real;
        float imag;

        for (iSep = 0; iSep < obj->nSeps; iSep++) {

            printf("\nSource index: %u\n",iSep);

            for (iBin = 0; iBin < obj->halfFrameSize; iBin++) {

                printf("(%03u): ",iBin);

                for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {

                    real = obj->array[iSep][iBin * obj->nChannels * 2 + iChannel * 2 + 0];
                    imag = obj->array[iSep][iBin * obj->nChannels * 2 + iChannel * 2 + 1];

                    printf("(%+1.2f + %1.2fi) ", real, imag);

                }

                printf("\n");

            }

        }
        
    }