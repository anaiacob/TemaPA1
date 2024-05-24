build:
	gcc main.c functii.c -o lanParty
run:
	./lanParty c.in d.in r.out

clean:
	rm -f lanParty
