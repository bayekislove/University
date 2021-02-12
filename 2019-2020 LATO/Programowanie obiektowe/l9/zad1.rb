class Funkcja
    def initialize(&blok)
        @tresc = blok
    end

    def oblicz(arg)
        @tresc.call(arg)
    end

    def pochodna(punkt)
        (@tresc.call(punkt + 0.00001) - @tresc.call(punkt)) / 0.00001
    end

    def miejsca_zerowe(a,b,e) #z tw Darboux
        m_z = 0; it = 0; kroczki = []
        kroczki.push(a*1.0)
        while a < b do
            kroczki.push(a + e)
            it += 1
            a += e
        end
        if kroczki.last() > b*1.0
            kroczki.delete(kroczki.last())
        end
        (1 ... kroczki.length()).each{ |i|
            (@tresc.call(kroczki[i])) * (@tresc.call(kroczki[i-1])) > 0 ? m_z += 0 : m_z += 1
        }
        return m_z
    end

    def pole(a,b) #całkuję numerycznie złożonym wzorem trapezów, wykonując 10000 kroków
        suma = 0.0
        suma += @tresc.call(a)
        suma += @tresc.call(b)
        (1 ... 10000).each{ |i|
            suma += @tresc.call(a + ((b-a) / 10000.0) * i) }
        suma = suma * ((b-a) / 10000.to_f)
        return suma
    end

end

test = Funkcja.new{ | x | x*x*Math.sin(x)}
puts(test.oblicz(3)) #wg Wolframa działa ;) 
puts(test.pochodna(3)) #wg Wolframa działa ;)
puts(test.pole(3,5)) #wg Wolframa działa ;)
puts(test.miejsca_zerowe(3,5,0.1)) #tu też działa

test2 = Funkcja.new{|x| Math.sin(x)}
puts(test2.miejsca_zerowe(0,10,0.001)) #wg wolphrama działa