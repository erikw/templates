# Ref: https://mg.readthedocs.io/latexmk.html

# Default top-level files to compile.
@default_files = ('letter.tex', 'paper.tex', 'slides.tex');

$pdf_mode = 1;					# tex -> pdf
#$use_make_for_missing_files = 1;		# Try generate missing files.
# %O and %S let latexmk inject its own flags and the source file path.
# -file-line-error prints compiler-style file:line diagnostics.
# -halt-on-error stops on the first LaTeX error instead of limping on.
# -interaction=nonstopmode keeps the run non-interactive for make/CI.
$pdflatex = 'pdflatex -file-line-error -halt-on-error -interaction=nonstopmode %O %S';
