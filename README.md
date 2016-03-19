# RayTracer
A whitted ray tracer written in C++

This project mainly serves the purposes of making me more familiar with C++ as well as getting me into computer graphics. I hope though, that it is helpful and/or educational for others too and I try to keep the code understandable, rather than highly performant.

It is written in C++11 and thus requires a compiler capable of that standard. It uses CImg for image import and export, which at least depends on X11 and pthread libraries. CImg dependencies are handled in its own `.cmake` file. It further depends on [PugiXML](https://github.com/zeux/pugixml) for XML parsing and uses [TinyOBJLoader](https://github.com/syoyo/tinyobjloader) as in-tree library.
