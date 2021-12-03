import threading
from typing import Dict, List
from bs4.element import NavigableString
from requests import get as reqGet
from bs4 import BeautifulSoup
from threading import Thread
from time import sleep

class HTMLSiteMonitoring:

    def __init__(self, site) -> None:
        self.continueMonitor = True
        self.url = site
    
    def setup(self):
        self.bsObj = BeautifulSoup(reqGet(self.url).text, 'html.parser')
        self.bsTags = self.bsObj.find_all()

    def pauseMonitoring(self):
        self.continueMonitor = False
        self.thread.join()
    
    def resumeMonitoring(self):
        self.continueMonitor = True

    def monitor(self):
        while self.continueMonitor:
            sleep(60)

            newbs = BeautifulSoup(reqGet(self.url).text, 'html.parser')
            newbsTags = newbs.find_all()

            ### Jeśli tagi mają jakieś dziecko które nie jest navigable stringiem i te same argumenty i nazwę 
            ### to ich nie rozpatrujemy, wiadomo wtedy że zmiana musiała zajść gdzieś niżej i tę zmianę niżej wypiszemy
            i = 0
            while i < len(self.bsTags):
                j = 0
                while j < len(newbsTags):
                    nonNavigChildsTag = list(filter(lambda x : not (type(x) == NavigableString), self.bsTags[i].contents))
                    nonNavigChildsNewtag = list(filter(lambda x : not (type(x) == NavigableString), newbsTags[j].contents))
                    ### tyle samo dzieci które nie jest navigable stringiem i ta liczba >0
                    if len(nonNavigChildsTag) == len(nonNavigChildsNewtag):
                        if (len(nonNavigChildsTag) == 0) and self.bsTags[i] is not newbsTags[j]:
                            j += 1
                            continue
                        elif (self.bsTags[i].name != newbsTags[j].name or self.bsTags[i].attr != newbsTags[j].attr):
                            j += 1
                            continue
                        del self.bsTags[i]
                        i -= 1
                        del newbsTags[j]
                        break
                    j += 1
                i += 1

            for el in self.bsTags:
                print(f"Removed: {el.text}")
            for el in newbsTags:
                print(f"Added: {el.text}")
            self.bsObj = newbs
            self.bsTags = newbsTags

            

class ReportHTMLChanges:

    def __setupThread(self, site):
        ret = HTMLSiteMonitoring(site)
        self.sitesToBS[site] = ret
        ret.setup()
    
    def __init__(self, sites : List[str]) -> None:
        self.sitesToBS = Dict()
        threads = []
        for site in sites:
            thread = Thread(targt=self.__setupThread, args=(site))
            threads.append(thread)
            thread.start()

        for thread in threads:
            thread.join()

    def startMonitoring(self):
        self.threads = []
        for (_, siteObj) in self.sitesToBS.items():
            thread = Thread(siteObj.monitor)
            thread.start()
            self.threads.append(thread)
    
    def stopMonitoring(self):
        for thread in self.threads:
            thread.join()


if __name__ == '__main__':
    #monitoring = HTMLmonitoring("http://google.com")
    a = BeautifulSoup('<div><a href="aaaa"/></div>', 'html.parser')
    b = BeautifulSoup('<div><a href="b"/></div>', 'html.parser')

    c = BeautifulSoup('<div><p>kkk</p<a href="aaaa"/></div>', 'html.parser')
    d = BeautifulSoup('<div><p>kkk</p><a href="b"/></div>', 'html.parser')
    