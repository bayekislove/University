from random import randint
from download_txt import save_txt_in_list

def uprosc_zdanie(zdanie, dl_slowa, liczba_slow):
    if len(zdanie) == 0:
        return ''
    words = list(filter( lambda x : len(x) <= dl_slowa, zdanie[:-1].split(' ') ))
    for _ in range(len(words) - liczba_slow):
        del words[randint(0, len(words) - 1)]
    if len(words) == 0:
        return ''
    words[0] = words[0].title()
    return ' '.join(words) + '.'

def uprosc_tekst(tekst, dl_slowa, liczba_slow):
    return ' '.join( list( map( lambda x : uprosc_zdanie(x, dl_slowa, liczba_slow), tekst.split(".") ) ) )

if __name__ == '__main__':
    tekst = save_txt_in_list('https://wolnelektury.pl/media/book/txt/pan-tadeusz.txt').replace('\n', ' ').replace('\r', ' ')
    tekst = ' '.join(tekst.split())
    print(uprosc_tekst(tekst, 13, 7))