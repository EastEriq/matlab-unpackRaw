#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include <libraw/libraw.h>
#include "mex.h"

#ifdef WIN32
  #include <windows.h>
  #include <sys/utime.h>
  #include <winsock2.h>
#else
  #include <unistd.h>
  #include <netinet/in.h>
#endif

void
mexFunction(int nlhs,mxArray *plhs[],int nrhs,const mxArray *prhs[])
{
    unsigned char *ImgData;
    LibRaw RawProcessor;
    char *filename, errmsg[160];
    int ret;
    
    # define verbose true

    /* check proper input and output */
    if(nrhs!=1)
        mexErrMsgIdAndTxt( "MATLAB:librawmex:invalidInput",
                "Filename input required.");
    else if(!mxIsChar(prhs[0]))
        mexErrMsgIdAndTxt( "MATLAB:librawmex:inputNotChar",
                "Input must be a string.");
    
    filename = mxArrayToString(prhs[0]);

    if (verbose)
      mexPrintf("Processing file %s\n", filename);
    if ((ret = RawProcessor.open_file(filename)) != LIBRAW_SUCCESS)
    {
      sprintf(errmsg,"Cannot open %s: %s\n", filename, libraw_strerror(ret));
      mexErrMsgIdAndTxt( "MATLAB:librawmex:cantOpenFile",errmsg);
    }
    
    #define S RawProcessor.imgdata.sizes

    if (verbose)
    {
      mexPrintf("Image size: %dx%d\nRaw size: %dx%d\n",
              S.width, S.height, S.raw_width, S.raw_height);
      mexPrintf("Margins: top=%d, left=%d\n", S.top_margin, S.left_margin);
    }

    if ((ret = RawProcessor.unpack()) != LIBRAW_SUCCESS)
    {
      sprintf(errmsg,"Cannot unpack %s: %s\n", filename, libraw_strerror(ret));
      mexErrMsgIdAndTxt( "MATLAB:librawmex:cantUnpack",errmsg);
    }

    if (verbose)
      mexPrintf("Unpacked....\n");

    if (!(RawProcessor.imgdata.idata.filters || RawProcessor.imgdata.idata.colors == 1))
    {
      mexPrintf("Only Bayer-pattern RAW files supported, sorry....\n");
    }

    plhs[0] = mxCreateNumericMatrix(S.raw_width,S.raw_height,mxUINT16_CLASS,mxREAL);
    uint16_t * pImage = (uint16_t*)mxGetData(plhs[0]);
    memcpy(pImage,RawProcessor.imgdata.rawdata.raw_image,S.raw_width*S.raw_height*2); 
}
