# Syntax Highlighting

## Shell Sessions
### Comparisions
Using `bash`
```bash
ls ~/
Applications  Desktop  Documents  Downloads  Library  Movies  Music  Pictures  Public  bak  bin  dl  doc  dropbox  media  src  tmp
tar xvzf some_tarball.tar.gz
file_1.c
file_2.h
file_2.c
file_2.h
rm -rf /  # Don't try this please
```

Using `bash session`
```bash session
ls ~/
Applications  Desktop  Documents  Downloads  Library  Movies  Music  Pictures  Public  bak  bin  dl  doc  dropbox  media  src  tmp
tar xvzf some_tarball.tar.gz
file_1.c
file_2.h
file_2.c
file_2.h
rm -rf /  # Don't try this please
```

Using `console`
```console
$ ls ~/
Applications  Desktop  Documents  Downloads  Library  Movies  Music  Pictures  Public  bak  bin  dl  doc  dropbox  media  src  tmp
Applications  Desktop  Documents  Downloads  Library  Movies  Music  Pictures  Public  bak  bin  dl  doc  dropbox  media  src  tmp
$ tar xvzf some_tarball.tar.gz
file_1.c
file_2.h
file_2.c
file_2.h
$ rm -rf /  # Don't try this please
```

### Conclusion
* Use `console` when you want to demonstrate output from commands as well as it looks to the user. Requires preceeding lines with `$ `.
* Use `bash` for commands that should be copy-and-pasteable for the user.
