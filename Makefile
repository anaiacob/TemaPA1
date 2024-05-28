build:
	gcc main.c functii.c AVL.c BST.c liste.c cozi.c stive.c -o lanParty
run:
	./lanParty c.in d.in r.out

clean:
	rm -f lanParty
