mex -lraw -outdir . -ULINUX librawmex.cpp
tic
ImgDat = librawmex(filename);
toc
imshow(ImgDat);
clear qhyccdmex;
