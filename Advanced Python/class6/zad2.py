from typing import Dict, List
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
                

if __name__ == '__main__':
    #monitoring = HTMLmonitoring("http://google.com")
    a = BeautifulSoup("<div><a href='gowno'/><div>a</div><div>chuj</div></div>", 'html.parser')
    for i in a.children:
        for k in i.children:
            print(k)