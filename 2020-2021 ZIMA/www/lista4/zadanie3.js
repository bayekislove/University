$(document).ready(function () {
    $("img").each(function () {
        $(this).data('marked', false);
    });

    $("img").on("click", function () {
        if ($(this).data('marked')) {
            $(this).css('border-width', '0px');
            $(this).data('marked', false);

            $("#all".data('marked', true));
        }
        else {
            $(this).css({
                'border-width': '7px',
                'border-style': 'solid',
                'border-color': 'darkred'
            });
            $(this).data('marked', true);

            var ifEveryImgMarked = true;
            $("img").each(function () {
                if (!$(this).data('marked'))
                    ifEveryImgMarked = false;
            })

            if (ifEveryImgMarked) {
                $("#all").html("Unmark");
                $("#all").data('marked', true);
            }
            else{
                $("#all").html("Mark");
            }
        }
    })

    $("#all").on('click', function () {
        if ($(this).data('marked')) {
            $("img").css('border-width', '0px');

            $(this).html("Mark");
            $(this).data('marked', false);
        }
        else {
            $("img").css({
                'border-width': '7px',
                'border-style': 'solid',
                'border-color': 'darkred'
            });
            $(this).html("Unmark");
            $(this).data('marked', true);
        }
        $("img").each(function(){
            $(this).data('marked', $("#all").data('marked'));
        })
    })

    $("#toLog").on('click', function () {
        let textlog_string = "";
        $("img").each(function () {
            if ($(this).data('marked'))
                textlog_string += $(this).attr('id') + " ;;; ";
        })
        $("#textLog").val(textlog_string);
    })
})
