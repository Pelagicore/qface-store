TEMPLATE = subdirs

{% for module in system.modules %}
SUBDIRS += {{module|lower|replace(".", "-")}}/{{module|lower|replace(".", "-")}}.pro
SUBDIRS += {{module|lower|replace(".", "-")}}/lib{{module|lower|replace(".", "-")}}.pro
{% endfor %}
