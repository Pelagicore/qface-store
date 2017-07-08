#!/usr/bin/env python3
# Copyright (c) Pelagicore AB 2016

import click
import logging
import logging.config
import yaml
from path import Path

from qface.generator import FileSystem, Generator
from qface.helper.qtcpp import Filters
from qface.helper.doc import parse_doc
from qface.watch import monitor
from qface.shell import sh
import qface.filters

here = Path(__file__).dirname()

logging.config.dictConfig(yaml.load(open(here / 'log.yaml')))

log = logging.getLogger(__file__)


def run(src, dst):
    log.debug('run {0} {1}'.format(src, dst))
    project = Path(dst).name
    classPrefix = ''
    system = FileSystem.parse(src)
    generator = Generator(search_path=here / 'templates')
    Filters.classPrefix = classPrefix
    generator.register_filter('returnType', Filters.returnType)
    generator.register_filter('parameterType', Filters.parameterType)
    generator.register_filter('defaultValue', Filters.defaultValue)
    generator.register_filter('parse_doc', parse_doc)
    generator.register_filter('hash', qface.filters.hash)
    generator.register_filter('signalName', Filters.signalName)
    generator.register_filter('parameters', Filters.parameters)
    generator.register_filter('signature', Filters.signature)
    generator.register_filter('open_ns', Filters.open_ns)
    generator.register_filter('close_ns', Filters.close_ns)
    generator.register_filter('using_ns', Filters.using_ns)

    ctx = {
        'dst': dst,
        'system': system,
        'classPrefix': classPrefix,
        'project': project,
    }

    dst = generator.apply('{{dst}}', ctx)
    generator.destination = dst

    generator.write('{{project}}.pro', 'project.pro', ctx)
    generator.write('stores/stores.pro', 'stores/stores.pro', ctx)
    generator.write('.qmake.conf', 'qmake.conf', ctx)

    generator.write('shared/shared.pri', 'shared/shared.pri', ctx)
    generator.write('shared/action.h', 'shared/action.h', ctx)

    for module in system.modules:
        ctx.update({'module': module})
        dst = generator.apply('{{dst}}/stores/{{module|lower|replace(".", "-")}}', ctx)
        generator.destination = dst

        generator.write('{{module|lower|replace(".", "-")}}.pro', 'stores/store/store.pro', ctx)
        generator.write('{{module|lower|replace(".", "-")}}.pri', 'stores/store/store.pri', ctx)
        generator.write('lib{{module|lower|replace(".", "-")}}.pro', 'stores/store/libstore.pro', ctx)
        generator.write('plugin.h', 'stores/store/plugin.h', ctx)
        generator.write('plugin.cpp', 'stores/store/plugin.cpp', ctx)
        generator.write('qmldir', 'stores/store/qmldir', ctx)

        for interface in module.interfaces:
            ctx.update({'interface': interface})
            generator.write('{{interface|lower}}store.h', 'stores/store/store.h', ctx, preserve=True)
            generator.write('{{interface|lower}}store.cpp', 'stores/store/store.cpp', ctx, preserve=True)
            generator.write('{{interface|lower}}storebase.h', 'stores/store/storebase.h', ctx)
            generator.write('{{interface|lower}}storebase.cpp', 'stores/store/storebase.cpp', ctx)
            generator.write('{{interface|lower}}state_p.h', 'stores/store/state_p.h', ctx)
            generator.write('{{interface|lower}}state.h', 'stores/store/state.h', ctx)
            generator.write('{{interface|lower}}state_p.h', 'stores/store/state_p.h', ctx)
            generator.write('{{interface|lower}}state.cpp', 'stores/store/state.cpp', ctx)


@click.command()
@click.option('--reload/--no-reload', default=False)
@click.option('cmd', '--exec', type=click.Path(exists=True), multiple=True)
@click.argument('src', nargs=-1, type=click.Path(exists=True))
@click.argument('dst', nargs=1, type=click.Path(exists=True))
def app(src, dst, reload, cmd):
    """Takes several files or directories as src and generates the code
    in the given dst directory."""
    if reload:
        script = Path(__file__).abspath()
        monitor(script, src, dst)
    else:
        run(src, dst)
        sh(cmd)


if __name__ == '__main__':
    app()
