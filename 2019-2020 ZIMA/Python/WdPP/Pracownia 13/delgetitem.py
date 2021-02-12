class ListItem:
    def __init__(self, e):
        self.e = e
        self.next = None
        
    def __str__(self):
        return str(self.e)    

class LinkedList:
    def __init__(self, elems):
        self.first = None
        self.last = None
        self.length = 0
        
        for e in elems:
            self.append(e)  
            
    def append(self, e):
        new = ListItem(e)
        if self.first == None:
            self.first = new
            self.last = new
        else:
            self.last.next = new
            self.last = new
        self.length += 1  
        
    def __len__(self):
        return self.length    
        
    def __iter__(self):
        elem = self.first
        while elem:
            yield elem.e
            elem = elem.next  

    def iterator_li(self):
        elem = self.first
        while elem:
            yield elem
            elem = elem.next
            
    def __getitem__(self, i):
        if i > 0:
            pos = 1
            for e in self:
                if pos == i:
                    return e
                pos += 1
        else:
            pos = 1
            for e in self:
                if pos == self.length - abs(i) + 1:
                    return e
                pos += 1
        raise IndexError 
        
    def __setitem__(self, i, a):     
        pos = 0
        for li in self.iterator_li():
            if pos == i:
                li.e = a
                return
            pos += 1
        raise IndexError 
        
    def __str__(self):
        elems = [str(e) for e in list(self)]
        # elems = map(str, list(elems))
        return '-[' + ', '.join(elems) + ']-'    
    
    def __delitem__(self, i):
        if i > self.length:
            return IndexError
        elif len(self) == 0:
            raise IndexError
        elif len(self) == 1:
            self.first = None
            self.last = None
        elif i == 1:
            self.first = self.first.next
        else:
            licznik = 1
            pom = self.first
            while(licznik != i-1):
                pom = pom.next
                licznik += 1
            pom.next = (pom.next).next
        self.length -= 1
        return

L = LinkedList([2,3,4,5,5,6,7])
L.__delitem__(2)
print(L)
L.__delitem__(6)
print(L)
L.__delitem__(1)
print(L)
print(L.__getitem__(1))
print(L.__getitem__(-1))


