from download_txt import save_txt_in_list

def kompresja(tekst):
    kolejne_wystapienia = 0
    poprzednia_literka = ''
    skompresowane = []
    for literka in tekst:
        if literka == poprzednia_literka:
            kolejne_wystapienia += 1
        else:
            skompresowane.append((kolejne_wystapienia + 1, poprzednia_literka))
            kolejne_wystapienia = 0
        poprzednia_literka = literka
    skompresowane.append((kolejne_wystapienia + 1, poprzednia_literka))
    return skompresowane[1:]

def dekompresja(tekst_skompresowany):
    test_po_dekompresji = []
    for (wystapienia, znak) in tekst_skompresowany:
        test_po_dekompresji.append(wystapienia * znak)
    return ''.join(test_po_dekompresji)

if __name__ == '__main__':
    tekst = save_txt_in_list('https://wolnelektury.pl/media/book/txt/pan-tadeusz.txt').replace('\n', ' ').replace('\r', ' ')
    tekst = ' '.join(tekst.split())
    print(dekompresja(kompresja(tekst)))
    print(kompresja('aaaa bbb...., kkki'))
    print(dekompresja(kompresja('aaaa bbb...., kkki')))