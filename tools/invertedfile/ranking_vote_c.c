/**
 * Ranking by votes
 * Input:
 * + inverted file
 * + list words of query image 
 * Return: vote score of images, ranked_list
 *
 *
 *
 */

#include "mex.h"
#include "inv_file.h"

#define NUM_DOCS    6392

void mexFunction( int nlhs, mxArray *plhs[],
                  int nrhs, const mxArray *prhs[])
{
    //size_t          nqwords = mxGetNumberOfElements(prhs[1]); 
    const invFile*  inv     = *(invFile**) mxGetData(prhs[0]);      // pointer to input inverted file
    int*            qwords  = mxGetPr(prhs[1]);                     // pointer to input data    (document - words list)
    size_t          nqwords = mxGetNumberOfElements(prhs[1]);  // lenght of input data     (number of words)
    mwSize          dims[2];
    int*            candidates;     // pointer store output candidates list
    int             ncands = 0;     // number of output candidates
    int             *pOutId,        // pointer to output (id and value)
                    *pOutVal; 
    int             i = 0,
                    j = 0;
    int             pos;
    
    printf("num query words: %d\n",nqwords);
    //for(i = 0; i < nqwords; i++)
    
    candidates = (int*)malloc(sizeof(int)*inv->num_docs);
    for(i = 0; i < inv->num_docs; i++) candidates[i] = 0;
    
    for(i = 0; i < nqwords; i++)
    {
        int w = qwords[i] - 1;
        //printf("words[%d] = %d\n", i, w);
        if(inv->size_pw[w] > 0)
        {
            for(j=0; j < inv->size_pw[w]; j++)
            {
                 int x = inv->inv_file[w][j];
                 candidates[x] ++;
            }
        }
    }
    
    for(i = 0; i < inv->num_docs; i++) if (candidates[i] > 0) ncands ++;
    
    dims[0] = 1;
    dims[1] = ncands;
    plhs[0] = mxCreateNumericArray(2, dims, mxUINT32_CLASS, mxREAL);
    pOutId = (int*)mxGetData(plhs[0]);
    plhs[1] = mxCreateNumericArray(2, dims, mxUINT32_CLASS, mxREAL);
    pOutVal = (int*)mxGetData(plhs[1]);
       
    pos = 0;
    for(i = 0; i < inv->num_docs; i++)
    {
        if (candidates[i] >0)
        {
            pOutId[pos] = i + 1;
            pOutVal[pos] = candidates[i];
            pos ++;
        }
    }
    
    quicksort(pOutId, pOutVal, 0, ncands-1);
}