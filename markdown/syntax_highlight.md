# Syntax Highlighting

## Shell Sessions
### Comparisions
### Plain commands
Using `bash`:
```bash
ls ~/
tar xvzf some_tarball.tar.gz
rm -rf /  # Don't try this please
```

Using `console`:
```console
ls ~/
tar xvzf some_tarball.tar.gz
rm -rf /  # Don't try this please
```


### Preceeding shell marker `$ `
Using `bash`:
```bash
$ ls ~/
$ tar xvzf some_tarball.tar.gz
$ rm -rf /  # Don't try this please
```

Using `console`:
```console
$ ls ~/
$ tar xvzf some_tarball.tar.gz
$ rm -rf /  # Don't try this please
```


### Command output
Using `bash`:
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


Using `console`:
```console
ls ~/
Applications  Desktop  Documents  Downloads  Library  Movies  Music  Pictures  Public  bak  bin  doc media  src  tmp
tar xvzf some_tarball.tar.gz
file_1.c
file_2.h
file_2.c
file_2.h
rm -rf /  # Don't try this please
```

### Command output + shell marker
Using `bash`:
```bash
$ ls ~/
Applications  Desktop  Documents  Downloads  Library  Movies  Music  Pictures  Public  bak  bin  doc media  src  tmp
$ tar xvzf some_tarball.tar.gz
file_1.c
file_2.h
file_2.c
file_2.h
$ rm -rf /  # Don't try this please
```


Using `console`:
```console
$ ls ~/
Applications  Desktop  Documents  Downloads  Library  Movies  Music  Pictures  Public  bak  bin  doc media  src  tmp
$ tar xvzf some_tarball.tar.gz
file_1.c
file_2.h
file_2.c
file_2.h
$ rm -rf /  # Don't try this please
```

### Conclusion
* Use `console` when you want to demonstrate output from commands as well as it looks to the user. Requires preceeding lines with `$ `.
* Use `bash` for commands that should be copy-and-pasteable for the user (no preceeding `$ `).

## Reference
* https://stackoverflow.com/questions/20303826/how-to-highlight-bash-shell-commands-in-markdown/49004070#49004070
* https://github.com/github/linguist/blob/3c3b037910006fc2f1a9bb34b2c4e9cde062206c/lib/linguist/languages.yml#L5842-L5843
