# stereo-fusionmove
Test of the QPBO fusion move for the dense matching stereo case from the article : http://www.robots.ox.ac.uk/~ojw/2op/
(Code of the article http://lcaraffa.net/posts/note-fusion-move-qpbo.html)

It uses QPOB and HOCR.
-http://pub.ist.ac.at/~vnk/software.html
-http://www.f.waseda.jp/hfs/software.html

Warning, this is a simple test, lot of things are not generic and should be adapted :)

## Install on linux
```{r, engine='bash', count_lines}
./build_unix.sh build
```
## Run example
```{r, engine='bash', count_lines}
./run_examples.sh 
```