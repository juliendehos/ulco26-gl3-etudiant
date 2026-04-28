
# youpi

## Description

Une application web/desktop joyeuse.

Exécutables :

    - `youpi-gui.out` : appli desktop, en gtkmm
    - `youpi-web.out` : appli web dynamique, avec libhv
    - `youpi-static.out` : génère des fichiers HTML/SVG statiques (cf le script `deploy.sh`)

## Planning

- [ ] implémenter le rendu SVG vers un fichier (classe `RendererSvg` + fonction `mkPageSvg` + `youpi-static.cpp`)
- [ ] implémenter la génération des pages HTML (`mkPageIndex` + `mkPageHtml` + `youpi-static.cpp`)
- [ ] tester la génération de pages statiques avec le script `deploy.sh`
- [ ] implémenter la génération de pages dynamiques (`youpi-web.cpp`)

## Références

- [libhv](https://github.com/ithewei/libhv)
- [DeepWiki libhv](https://deepwiki.com/ithewei/libhv)
- [libhv http server](https://github.com/ithewei/libhv/blob/master/examples/http_server_test.cpp)
- [Programming with gtkmm 4](https://gnome.pages.gitlab.gnome.org/gtkmm-documentation/index.html)
- [Gtk Namespace Reference](https://gnome.pages.gitlab.gnome.org/gtkmm/namespaceGtk.html)

