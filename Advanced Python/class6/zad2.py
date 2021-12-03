from typing import Dict, List
from bs4.element import NavigableString
from requests import get as reqGet
from bs4 import BeautifulSoup


class HTMLmonitoring:

    def __init__(self, site=None) -> None:
        self.sitesToWatch : Dict[str, BeautifulSoup] = {}
        self.continueMonitor = True
        if site != None:
            self.addSiteToLookAfter(site)

    def addSiteToLookAfter(self, site):
        self.sitesToWatch[site] = BeautifulSoup(reqGet(site).text, 'html.parser')

    def pauseMonitoring(self):
        self.continueMonitor = False
    
    def resumeMonitoring(self):
        self.continueMonitor = True

    def monitor(self):
        while self.continueMonitor:
            for url, bs in self.sitesToWatch.items():
                newbs = BeautifulSoup(reqGet(url).text, 'html.parser')
                bsTags = bs.find_all()
                newbsTags = newbs.find_all()

                ### Jeśli tagi mają jakieś dziecko które nie jest navigable stringiem i te same argumenty i nazwę 
                ### to ich nie rozpatrujemy, wiadomo wtedy że zmiana musiała zajść gdzieś niżej i tę zmianę niżej wypiszemy
                i = 0
                while i < len(bsTags):
                    j = 0
                    while j < len(newbsTags):
                        nonNavigChildsTag = list(filter(lambda x : not (type(x) == NavigableString), bsTags[i].contents))
                        nonNavigChildsNewtag = list(filter(lambda x : not (type(x) == NavigableString), newbsTags[j].contents))
                        ### tyle samo dzieci które nie jest navigable stringiem i ta liczba >0
                        if len(nonNavigChildsTag) == len(nonNavigChildsNewtag):
                            if (len(nonNavigChildsTag) == 0) and bsTags[i] is not newbsTags[j]:
                                j += 1
                                continue
                            elif (bsTags[i].name != newbsTags[j].name or bsTags[i].attr != newbsTags[j].attr):
                                j += 1
                                continue
                            del bsTags[i]
                            i -= 1
                            del newbsTags[j]
                            break
                        j += 1
                    i += 1

                for el in bsTags:
                    print(f"Removed: {el.text}")
                for el in newbsTags:
                    print(f"Added: {el.text}")

def func(bs : BeautifulSoup, newbs : BeautifulSoup):
    bsTags = bs.find_all()
    newbsTags = newbs.find_all()   
    
    ### Jeśli tagi mają jakieś dziecko które nie jest navigable stringiem i te same argumenty i nazwę 
    ### to ich nie rozpatrujemy, wiadomo wtedy że zmiana musiała zajść gdzieś niżej i tę zmianę niżej wypiszemy
    i = 0
    while i < len(bsTags):
        j = 0
        while j < len(newbsTags):
            nonNavigChildsTag = list(filter(lambda x : not (type(x) == NavigableString), bsTags[i].contents))
            nonNavigChildsNewtag = list(filter(lambda x : not (type(x) == NavigableString), newbsTags[j].contents))
            ### tyle samo dzieci które nie jest navigable stringiem i ta liczba >0
            if len(nonNavigChildsTag) == len(nonNavigChildsNewtag):
                if (len(nonNavigChildsTag) == 0) and bsTags[i] is not newbsTags[j]:
                    j += 1
                    continue
                elif (bsTags[i].name != newbsTags[j].name or bsTags[i].attr != newbsTags[j].attr):
                    j += 1
                    continue
                del bsTags[i]
                i -= 1
                del newbsTags[j]
                break
            j += 1
        i += 1          

    for el in bsTags:
        print(f"Removed: {el}")
    for el in newbsTags:
        print(f"Added: {el}")


if __name__ == '__main__':
    #monitoring = HTMLmonitoring("http://google.com")
    a = BeautifulSoup('<div><a href="aaaa"/></div>', 'html.parser')
    b = BeautifulSoup('<div><a href="b"/></div>', 'html.parser')

    c = BeautifulSoup('<div><p>kkk</p<a href="aaaa"/></div>', 'html.parser')
    d = BeautifulSoup('<div><p>kkk</p><a href="b"/></div>', 'html.parser')
    