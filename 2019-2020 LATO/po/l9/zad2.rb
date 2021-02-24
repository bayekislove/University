class Funkcja2
    def initialize(&blok)
        @tresc = blok
    end

    def oblicz(x, y)
        @tresc.call(x,y)
    end

    def objetosc(a, b, c, d) #reguła punktu środkowego, wyznaczane numerycznie
        v = 0
        n = (b-a) / 1000.0 #długość kroczku po a b
        m = (d-c) / 1000.0 #dlugosc kroczku po c d
        (1 ... 1000).each do |i|
            (1 ... 1000).each do |j|
                v += @tresc.call(a + n * i + n/2.0, c + m * j + m/2.0)
            end
        end
        return v * n * m
    end

    def poziomica(a,b,c,d,dpoz,wysokosc) #z tw Darboux
        xy = []; it = 0; kroczki = []
        cstart = c
        kroczki.push([a*1.0,c*1.0])
        while a + dpoz <= b do
            a += dpoz
            while c + dpoz < d do
                c += dpoz
                kroczki.push([a, c])
            end
            c = cstart
        end
        
        (1 ... kroczki.length()).each{ |i|
            pom = @tresc.call(kroczki[i][0],kroczki[i][1]) - wysokosc
            if pom * (@tresc.call(kroczki[i][0]-dpoz, kroczki[i][1]) - wysokosc) < 0
                xy.push([kroczki[i][0],kroczki[i][1]])
            elsif pom * (@tresc.call(kroczki[i][0]+dpoz, kroczki[i][1]) - wysokosc) < 0
                xy.push([kroczki[i][0],kroczki[i][1]])
            elsif pom * (@tresc.call(kroczki[i][0], kroczki[i][1] - dpoz) - wysokosc) < 0
                xy.push([kroczki[i][0],kroczki[i][1]])
            elsif pom * (@tresc.call(kroczki[i][0], kroczki[i][1] + dpoz) - wysokosc) < 0
                xy.push([kroczki[i][0],kroczki[i][1]]) 
            end
        }
        return xy
    end
    
end

test = Funkcja2.new{|x,y| x+y}
puts(test.oblicz(1,3))
puts(test.objetosc(0,3,0,3)) #wolfram szczęśliwie się zgadza, błąd to 0.03
print(test.poziomica(0.0,1.0,0.0,1.0,0.01,3))