postmarketos_welcome_sources = [
  'main.c',
  'postmarketos_welcome-window.c',
]

postmarketos_welcome_deps = [
  dependency('gio-2.0', version: '>= 2.50'),
  dependency('gtk+-3.0', version: '>= 3.22'),
  dependency('libhandy-1', version: '>= 1.0.0'),
]

gnome = import('gnome')

postmarketos_welcome_sources += gnome.compile_resources('postmarketos_welcome-resources',
  'postmarketos_welcome.gresource.xml',
  c_name: 'postmarketos_welcome'
)

executable('postmarketos-welcome', postmarketos_welcome_sources,
  dependencies: postmarketos_welcome_deps,
  install: true,
)
