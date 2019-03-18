if ispc
else
    % on ubuntu, needs the package libraw-dev (which depends on libraw15
    %  and liblcms2-dev)
    mex -lraw -outdir . -ULINUX unpackRaw.cpp
end

