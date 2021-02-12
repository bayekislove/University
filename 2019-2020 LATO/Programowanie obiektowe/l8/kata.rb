def array_diff(a, b)
    b.each do |item|
     if a.include?(item)
      a.delete(item)
     end
    end
    return a
  end

print(array_diff([1,2,3],[1]))