Marcu-Nicolescu Cezar-George
335CB

    Voi secventiona explicatiile temei in functie de cerintele avute, mai exact pentru fiecare task.
Task1 - realizarea ecuatiei prin intermediul functiilor puse la dispozitie din libraria cblast.
Pentru rezolvarea acestui task am avut nevoie de 2 matrici aditionale, una in care am stocat A^2, iar cealalata in care am salvat rezultatul produsului A^2 * B.
Pentru B * A transpus nu am avut nevoie de inca o matrice auxiliara pentru ca am salvat in B direct rezultatul.
Am copiat in matricea alpha toata matricea A cu ajutorul functiei cblas_dcopy, iar apoi am realizat inmultirea stocand in alpha rezultatele acesteia.
Pentru A^2 * B am mers pe acelasi principiu, preferand sa copiez in beta continutul matricii B, iar apoi a fost folosita pe post de rezultat al produsului dorit.
Pentru aceste 2 calcule am folosit cblas_dtrmm cu aceleasi optiuni , nu am avut nevoie de transpusa si nici sa modific pozitia matricilor de inmultit.

cblas dtrmm  optiuni pt inmultirile prezentate mai sus: 
    101 - order-ul , in cazul nostru , row major
    141 - side-ul , daca preferi A * B sau B * A, in acest caz respecta ordinea scrierii matricilor ca parametrii
    121 - uplo, specifica daca matricea este superior/inferior triangulara. A-ul este superior triangulara.
    111 - transpose, specifica daca inmultirea ar trebui sa fie facuta cu transpusa unei matrici sau nu, in cazul actual nu
    131 - unit, descriptor pt matricea triangulara.

Pentru efectuarea inmultirii B * A transpus parametrii difera, am modificat side-ul , pt ca de data aceasta mi-am dorit B * op(A), nu op(A) * B si am inclus ca imi doresc ca operatia sa fie executata cu transpusa lui A.
    Optiuni diferite pt dtrmm: 112, 142.

Task2 - Realizarea ecuatiei intr-o maniera neoptimizata

    Mai intai am realizat transpusa matricii A prin conceptul de linie ce devine coloana.
    Apoi am continuat prin a inmulti matricile ce imi sunt necesare calcularii produsului finit.
    Anumite foruri le-am optimizat putin deoarece A-ul este matrice superior triunghiulara.
    De exemplu , in momentul in care am calculat A^2 , am luat in considerare doar elementele de dupa diagonala principala , j-ul si k-ul fiind initializate de la i.
    Pentru A^2 * B am pornit cu for-ul specific parcurgerilor pe linii din A^2 si pe coloane matricei B tot de i pentru a respecta proprietatea matricii superior triunghiulare A^2.
    
Task3 - Realizarea unei variante optimizate

    Pentru a putea reduce numarul de computatii ale procesorului am preferat sa folosesc pointeri pentru a parcurge matricile.
    Pentru eficienta in transferul de date dintre cache si procesor am preferat sa foloseste registrii .
    Am salvat timp pentru ca variabilele nu mai erau incarcate in memoria cache atat de des si timpul de calcul a avut un impact imens in momentul in care am folosit pointeri.
    Numarul de calcule pe care le face procesorul pentru accesarile la memoriei atunci cand iau valoarea de la o anumita pozitie este inlocuita cu parcurgerea memoriei prin pointeri.
    Ca sa trec de la un element de pe o coloana la cel de sub el adaug N , ca sa trec de la un element de pe o linie la urmatorul adaug pur si simplu 1 la pointerul actual.
   
    Am pastrat structura de la neopt si am pus in aplicare cunostintele dobandite de la laboratorul 5.

Task4 - Flaguri pentru optimizari
    Am cautat pentru inceput flaguri ce imi activeaza grupuri de flaguri pt optimizari , de exemplu : -funroll-loops si -ffast-math, ca apoi sa imi dau seama ce optimizari sunt relevante pentru acest task.
    -ffast-math defineste macro-ul _FAST_MATH_ al preprocesorului si poate fi afectat de anumite implementari matematice ale functiilor.
    Acest flag activeaza : -fno-math-errno, -funsafe-math-optimizations, -ffinite-math-only, -fno-rounding-math, -fno-signaling-nans, -fcx-limited-range, -fexcess-precision=fast.
    Cel mai important ar fi -fexcess-precision=fast ce implica faptul ca operatiile pot fi transportate cu o precizie mai mare decat tipurile ce le definesc.
    -funsafe-math-optimizations -> ajuta la optimizari pentru variabile in virgula mobila si operatii aritmetice pe aceste numere.
    -fno-signaling-nans -> un flag pentru protectie mai mult ce dezactiveaza optimizari care pot schimba numerul de exceptii vizibile si semnalate

    Pentru a doua grupare de flaguri pe care urmeaza sa o extind mai jos am folosit -funroll-loops ce imi desface loopuri ale caror numar de iteratii pot fi vizibile la compilare.
    Acest flag le activeaza pe urmatoarele : -frerun-cse-after-loop, -fweb, -frename-registers
    -frerun-cse-after-loop : refoloseste subexpresiile comune dupa ce optimizarile pe loop-uri au fost efectuate.
    -frename-registers : exploateaza la maximum registrii procesorului si elimina dependetele false din timpul planificarii code-ului
    -fweb : construieste un fel de pseudo registrii ce inainte erau folositi pentru alocarea registrilor , astfel facandu-se o trecere mai usoara si rapida de la alocare la prelucrare.

    Aceste optimizari sunt evident eficiente pentru prelucrarea pe matrici , majoritatea dintre ele manipuland registrii si facand treceri mai eficiente ale datelor in procesor.
    Putem discuta si de optimizarile pe numerele din virgula mobila , ce au suferit si ele schimbari in urma activarii flagurilor, transferul de date fiind unul mai eficient datorita preciziei extinse.
    Nivelul de imbunatatire este de undeva la 8% - 9%, daca pun direct flagurile ce activeaza acele grupari sare undeva la 10 - 11%.

Task5 - Interpretare grafice si a performantelor in functie de N

	Am ales sa apelez la inca 2 variante de dimensiuni pentru matrici , prima dintre ele este 1000 , a doua 1400 , pentru a vedea cum evolueaza panta in graficele facute.
	In primul rand am observat ca , odata cu cresterea lui N , panta curbei devine din ce in ce mai mare , functia de crestere a timpului in raport cu dimensiunea fiind una exponentiala . Puterea de calcul este influentata foarte mult de numarul de operatii care ar trebui sa fie facute atat cu memoria cat si cu computatia efectiva. Presupun ca si in Cblas , chiar daca este atenuata mult mai eficient functia , tot se ajunge la a avea o crestere semnificativa a pantei daca valorile sunt suficient de mari. Orice mic detaliu conteaza in astfel de situatii , o atenuare abia vizibila prinde proportii atunci cand te joci cu dimensiuni extrem de mari .
	In fiecare grafic panta pare a fi aceeasi , insa nu sunt scalate la aceeasi unitate de timp. Daca ar fi sa ne raportam la acelasi interval masurat de timp atunci s-ar sesiza diferente intre momentele in care pantele incep sa creasca rapid.