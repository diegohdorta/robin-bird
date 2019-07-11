# The Robin Bird Library

[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)

Robin Bird is a small and flexible machine learning library, written in C++, that
aims to provide simple and extensible implementations of machine learning algorithms.
Robin Bird along with
[NXP eIQ(TM) Machine Learning Enablement](https://www.nxp.com/docs/en/nxp/user-guides/UM11226.pdf)
allows ways for solving real world problems on embedded systems.

# Getting Started with Robin Bird

Use the next commands to generate a full `Robin Bird` guide before diving into
the library. This documentation<sup>1</sup> can provide a complete understanding
of the entire application programming interface, functions and binaries:
```bash
$ gem install bundler
$ cd docs/
$ bundle install
$ bundle exec rake build
```

Read the documentation online on [therobinbird.org](https://diegohdorta.github.io/robin-bird-page/).

## Reading

The guides are saved in `docs/pdf` and `docs/html` folders. Use any PDF reader
tool or a web browser to read the documentation as follows:

```bash
$ evince pdf/robinbird.pdf
$ firefox html/robinbird/.html
```

# Maintainer

* Diego Dorta <diego.dorta@nxp.com>

<sup>1</sup> For more information about [Asciidoctor](https://asciidoctor.org/).
