Description
===========

Reads a mpls file and returns a dictionary, not a clip. There are two elements in the dictionary. The element with the key 'clip' contains a list of full path to each m2ts file in the playlist. The element with the key 'count' contains the number of m2ts file in the playlist.


Usage
=====

    mpls.Read(string source)

* source: The full path of the mpls file. Don't use relative path.

After obtaining the dictionary, you can use your favorite source filter to open them all with a for-loop and splice them together. For example:
```python
mpls = core.mpls.Read('D:/rule6/BDMV/PLAYLIST/00001.mpls')
ret = core.std.Splice([core.ffms2.Source(mpls['clip'][i]) for i in range(mpls['count'])])
```
