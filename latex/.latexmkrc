# Ref: https://mg.readthedocs.io/latexmk.html

# Default top-level files to compile.
@default_files = ('letter.tex', 'paper.tex', 'slides.tex');

$pdf_mode = 1;					# tex -> pdf
#$use_make_for_missing_files = 1;		# Try generate missing files.
$pdflatex = 'pdflatex -file-line-error -halt-on-error -interaction=nonstopmode %O %S';	# Print compiler-like error messages and stop promptly on errors.
