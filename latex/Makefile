# Compile a LaTeX file to different output formats.
# Inspired latexmk(1) usage from: http://tex.stackexchange.com/questions/40738/how-to-properly-make-a-latex-project
NAME=paper

# Force latexmk to always run by making $(NAME).pdf a phony target.
.PHONY: all clean help open wc $(NAME).dvi $(NAME).ps $(NAME).pdf

# target: all - Default target. Cleans and compiles.
#all: $(NAME).pdf  $(NAME).dvi $(NAME).ps # latexmk generates new .dvi even though input files have not changed.
all: $(NAME).pdf

# target: help - Display all targets.
help:
	egrep "#\starget:" [Mm]akefile  | cut -d " " -f3-

# target: clean - Deletes all generated files.
clean:
	latexmk -C
	$(RM) $(NAME).bbl # Remove Bibtex file.
	$(RM) $(NAME).tpt # Remove PDF thumbnails.

# target: wc - Count real words in the tex file.
wc:
	bin/texcount	$(NAME).tex

# target: cc - Count real characters in the tex file.
cc:
	bin/untex/untex	$(NAME).tex | wc -c

# target open - open the produced PDF file.
open: $(NAME).pdf
	gnome-open $<

# target checkrefs - Check for unused references with https://github.com/cereda/checkcites
checkrefs: $(NAME).aux
	texlua ${HOME}/src/checkcites/checkcites.lua --all $(NAME).aux


$(NAME).dvi $(NAME).ps: $(NAME).tex
	latexmk -silent -use-make -dvi -ps $<

$(NAME).pdf: $(NAME).tex
	latexmk -silent -use-make -pdf -pdflatex="pdflatex -interaction nonstopmode -file-line-error" $<

# Called by latexmk. Adding a $(NAME).pdf dependency would cause infinite recursion by latexmk.
$(NAME).tpt:
	thumbpdf $(NAME).pdf

