class Jawne
    def initialize(napis)
        @napis = napis
    end

    def zaszyfruj(klucz)
        zwrot = ""
        @napis.each_char do |literka|
            if klucz.assoc(literka) == nil
                zwrot += literka
            else
                zwrot += klucz[literka]
            end
        end
        return Zaszyfrowane.new(zwrot)
    end

    def reprezentacja()
        return @napis
    end
end


class Zaszyfrowane
    def initialize(napis)
        @napis = napis
    end

    def odszyfruj(klucz)
        klucz = klucz.invert
        zwrot = ""
        @napis.each_char do |literka|
            if klucz.assoc(literka) == nil
                zwrot += literka
            else
                zwrot += klucz[literka]
            end
        end
        return Jawne.new(zwrot)
    end

    def reprezentacja()
        return @napis
    end
end

H = Hash[" " => " ", "a" => "b", "b" => "c", "c" => "d", "d" => "e",
    "e" => "f", "f" => "g", "g" => "h", "h" => "i", "i" => "j",
    "j" => "k", "k" => "l", "l" => "m", "m" => "n", "n" => "o",
    "o" => "p", "p" => "r", "r" => "s", "s" => "t", "t" => "u",
    "u" => "v", "v" => "w", "w" => "x", "x" => "y", "y" => "z", "z" => "a"]

jeszczejawne = Jawne.new("jaroslaw kaczynski zbawca polski")
juzzaszyfrowane = jeszczejawne.zaszyfruj(H)
puts(juzzaszyfrowane.reprezentacja)

odszyfrowane = juzzaszyfrowane.odszyfruj(H)
puts(odszyfrowane.reprezentacja)