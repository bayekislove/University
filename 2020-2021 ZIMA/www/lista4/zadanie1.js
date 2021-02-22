$(document).ready(function(){
    $('#search').change(() => {
        if ($('#search').val().length >= 3){
            $('ul li').each(function(){
                let searched_index = ($(this).text().indexOf($('#search').val()));
                let thi_text = $(this).text();
                if (searched_index != -1){
                    $(this).text("");

                    var f_span = $(document.createElement('span'));
                    f_span.text(thi_text.substring(0, searched_index));
                    f_span.css("background-color", "#DCDCDC");
                    $(this).append(f_span);

                    var m_span = $(document.createElement('span'));
                    m_span.text(thi_text.substring(searched_index, $('#search').val().length + 1));
                    m_span.css("background-color", "#EEE8AA");
                    $(this).append(m_span);

                    var l_span = $(document.createElement('span'));
                    l_span.text(thi_text.substring($('#search').val().length + 1));
                    l_span.css("background-color", "#DCDCDC");
                    $(this).append(l_span);
                }
                else{
                    $(this).text("");
                    var pom_span = $(document.createElement('span'));
                    pom_span.text(thi_text);
                    $(pom_span).css("background-color", "#DCDCDC");
                    $(this).append(pom_span);
                }
            })
        }
    })
});