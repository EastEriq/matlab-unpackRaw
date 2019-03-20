## on Ubuntu

The package to be installed is `libraw-dev` (which depends on `libraw15`
and `liblcms2-dev`)

## on windows

The library package
(sources+compiled) can be downloaded from https://www.libraw.org/download

`libraw.dll` from `\bin\` needs also to be copied in this directory
 - is there perhaps a smarter way of building the mex?

## Use

`img=unpackRaw(raw_image_file)` % retrieves an uint16 grayscale

`img=unpackRaw(raw_image_file,'color')` % retrieves a single three-channel image

In principle there is a lot of metadata stored together with the raw
image, which could be retrieved and passed to Matlab from the structures of
`LibRaw`. Camera information, color map, etc. etc. I wanted to keep
things as simple as possible to start with.
