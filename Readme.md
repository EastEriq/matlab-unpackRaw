## on Ubuntu

The package to be installed is `libraw-dev` (which depends on `libraw15`
and `liblcms2-dev`)

## on windows

The library package
(sources+compiled) can be downloaded from https://www.libraw.org/download

`libraw.dll` from `\bin\` needs also to be copied in this directory 
 - is there perhaps a smarter way of building the mex?

## Use

`img=unpackRaw(raw_image_file)`

For the Nikon D700, the result is a rotated image. Probably this could
be fixed with a more complex code, reading the image metadata.

In principle there is a lot of metadata stored together with the raw
image, which could be retrieved and passed to Malab with functions of
`libraw`. Camera information, color map, etc. etc. I wanted to keep
things as simple as possible to start with.
