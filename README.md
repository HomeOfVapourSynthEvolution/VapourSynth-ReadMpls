# ReadMpls
Get m2ts clip id from a playlist and return a dict.

There are three elements in the dict:
- key 'count' contains the clip counts in the playlist.
- key 'clip' contains a list of full paths to each m2ts file in the playlist.
- key 'filename' contains a list of file names of each m2ts file in the playlist.


## Usage
    mpls.Read(string bd_path, int playlist[, int angle=0])

- bd_path: Full path to the root of Blu-ray disc or directory. Don't use relative path and don't contain a trailing slash at the end.

- playlist: Playlist number, which is the number in mpls file name.

- angle: Angle number to select in the playlist.


After obtaining the dict, you can use your favorite source filter to open them all with a for-loop and splice them together. For example:

```python
mpls = core.mpls.Read(r'D:\Downloads\rule6', 0)
clip = core.std.Splice([core.ffms2.Source(mpls['clip'][i]) for i in range(mpls['count'])])
```

If you want to put ffms2's index file at another place rather than the same directory of the source file, here is the example:

```python
mpls = core.mpls.Read(r'D:\Downloads\rule6', 0)
clips = []
for i in range(mpls['count']):
    clips.append(core.ffms2.Source(source=mpls['clip'][i], cachefile=r'D:\indices\rule6\' + mpls['filename'][i] + '.ffindex'))
clip = core.std.Splice(clips)
```


## Compilation
Requires `libbluray`.

```
meson build
ninja -C build
ninja -C build install
```
