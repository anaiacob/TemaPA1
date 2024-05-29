    Tema intitulata "LanParty" simuleaza functionalitatea unor meciuri a unui joc prin eliminarea echipelor, astfel, in cele ce urmeaza voi explica ce am utilizat:

    ->am citit cerintele din fisierele de intrare, deoarece aplicatia avea 4 task-uri si mai multe teste diverse de verificat
    ->la task 1 trebuia retinute numele echipelor intr-o lista si puse in fisiere fiecare pe un rand, astfel:
        -> pentru a putea retine echipele am folosit o lista dublu inlantuita a caror noduri aveau in structura lor:  ->numele echipei
                    ->un vector alocat dinamic cu dimensiune stiuta din datele de intrare in care se retineau numele jucatorilor din echipa si scorul lor
                    -> nr de puncte totale
        ->am adaugat la inceput pt complexitate temporala de O(1) 
        ->am utilizat 2 functii care citesc caractere dintr-un fisier pana ajung la final de linie sau document, diferenta dintre cele 2 este ca una dintre ele va citi doar incepand de le o anumita pozitie din fisier
        ->fiindca am alocat dinamic lista de echipe ce contine vectori de jucatori am si eliberat memoria printr-o functie

    -> la task 2 se elimina echipele cu scorul cel mai mic astfel incat sa ramana nr de echipe egal cu o putere a lui 2, astfel:
        ->am creat o functie care calculeaza puterea lui 2 mai mica sau egala cu nr de echipe intrate in joc
        ->am eliminat nr_echipe-2^m echipe prin stergerea nodurilor din lista dublu inlantuita de echipe
        ->pt a afla ce echipe trebuie eliminate am creat un vector cu scorurile totale si l-am sortat prin metoda QuickSort
        ->am cauta prin lista echipele care corespund scorurilor cele mai mici si le-am sters din lista
        -> in documentul de iesire am pus numele echipelor care au ramas
        ->am retinut lista pentru urmatoarele task-uri

    ->la task 3 trebuia create meciurile si eliminate echipele pierzatoare, astfel:
        ->am creat o coada in care am retinut toate echipele din lista
        -> am scos pe rand cate 2 pt realizarea meciurillor, iar comparandu-le in functie de scor le retineam intr-o stiva de pierzatori si de castigatori
        -> stiva de pierzatori o foloseam pt a sterge din lista echipele pierzatoare si a returna o alta lista cu castigatorii 
        -> stiva de castigatori o foloseam pt a pune in fisier numele echipelor castigatoare si pentru a crea o lista de echipe ramase care urmeaza a fi puse iar in meciuri, repetand procesul pana cand ramane o singura echipa castigatoare
        -> cand raman 8 echipe retin intr-o lista echipele pentru a le folosi la task 4

    ->la task 4 trebuie realizat un arbore BST pt a ordona echipele descrescator in functie de punctajele obtinute si in caz de egalitate in functie de ordinea lexicografica
        ->am creat arborele prin functiile aferente (creare nod, adaugare etc) si am retinut intr-o noua lista echipele ordonate prin BST pentru realizarea task-ului 5 in care se construieste un AVL

    ->la task 5 am creat un AVL si am afisat nodurile de pe level 2


Dificultati:
    ->faptul ca fisierul rezultat era diferit prin cativa biti de cel fata de care se compara prin sfarsitul de linie, trebuind sa folosesc \r\n (foarte enervant PS: mi-a luat mult sa imi dau seama)
    ->spatiile de dupa numele echipelor, pe care le-am eliminat
    ->asezarea echipelor in runde, trebuind sa imi dau seama pana unde trebuie sa fie textul
    ->la avl la rotatii la testul 14 nu-mi dadea,fiindca erau echipe cu acelasi scor si nu le comparam lexicografic pt rotatii
