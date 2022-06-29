# Sonderzeichen '<', '>' und '&' ins HTML-Format
s/&/\&amp;/g
s/</\&lt;/g
s/>/\&gt;/g
# Zeile 1 selelektieren wir mit insert für den HTML-Header
1 i\
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"\
"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">\
<html>\
<head>\
<title>\
Converted with txt2html.sed\
</title>\
</head>\
<body>\
<pre>
# Hier kommt der Text der Datei hin
# Mit append hängen wir den Footer ans Ende
$ a\
</pre>\
</body>\
</html>
