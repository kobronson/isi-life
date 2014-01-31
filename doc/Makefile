
SRC= Makefile isi-dokumentacja.tex bibliografia.bib

# pdf, ps, gs, gs2, dvi
default: t.ps

pdf: t.pdf
	echo "Making DVI to PDF"

ps: t.ps

gs: t.ps
	gv -scale -2 -geometry +0+0 isi-dokumentacja.ps

gs2: t.ps
	psnup -2 t.ps > tt.ps
	gv -landscape -scale -1 -geometry +0+0 tt.ps

dvi: t.dvi
	@xdvi + -s 4 -topmargin 6cm -bg white -keep -geometry 715x724+0+0 isi-dokumentacja

ed:
	vim isi-dokumentacja.tex

t: default


t.dvi: $(SRC)
	latex isi-dokumentacja
	latex isi-dokumentacja
	bibtex isi-dokumentacja
	latex isi-dokumentacja 
	latex isi-dokumentacja

t.pdf: t.dvi
	dvipdf t.dvi

t.ps: t.dvi
	dvips isi-dokumentacja.dvi -o isi-dokumentacja.ps

tgz: clean
	( D=`basename $$PWD`; cd ..; tar czf $$D.tgz $$D; ls -l $$D.tgz )

aspell:
	aspell --lang=pl  -t check isi-dokumentacja.tex
	
v: t t.ps

clean:
	rm -f *.dvi *.bbl *.blg *.log *.toc *.aux *.ps *.lof *.pdf

