class Fixnum
    def czynniki()
        results = []
        i = 1
        while i <= self do 
            if self % i == 0
                results.push(i)
            end
            i += 1
        end
    return results
    end

    def ack(y)
        if self == 0
            return y + 1
        elsif y == 0
            return (self - 1).ack(1)
        else 
            return (self - 1).ack(self.ack(y-1))
        end
    end

    def doskonala()
        pom_tab = self.czynniki
        sum = 0
        pom_tab.each{|item|
            sum = sum + item}
        return sum == sum - self
    end

    def slownie()
        pom_tab = {0=> "zero", 1=> "jeden", 2=> "dwa", 3=> "trzy", 4=> "cztery", 5=> "piec", 6=> "szesc", 7=> "siedem", 8=> "osiem", 9=> "dziewiec"}
        zwrot = ""
        pom = self
        while pom != 0 do
            zwrot = pom_tab[pom % 10] + " " + zwrot
            pom = pom / 10
        end
        return zwrot
    end
end

puts(2.ack(1))
puts(496.doskonala)
puts(4.slownie)
puts(1243.slownie)
