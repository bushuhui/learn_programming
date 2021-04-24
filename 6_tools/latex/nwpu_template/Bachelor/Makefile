default:
	xelatex main.tex
all:
	xelatex main.tex
	bibtex main
	xelatex main.tex
	xelatex main.tex

clean:
	find -name "*.aux" -exec rm -v {} \;
	find -name "*.blg" -exec rm -v {} \;
	find -name "*.thm" -exec rm -v {} \;
	find -name "*.log" -exec rm -v {} \;
	find -name "*.out" -exec rm -v {} \;
	find -name "*.toc" -exec rm -v {} \;
	find -name "*.bbl" -exec rm -v {} \;
