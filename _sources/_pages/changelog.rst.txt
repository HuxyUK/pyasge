ChangeLog
=========

Version 1.0.0b3
---------------

:Date: May 11, 2021

* Added property to access desktop resolution (`#7eac3cb <https://github.com/HuxyUK/pyasge/commit/7eac3cbcfe594cfa0725e9b3c20e795b9ef61530>`__)
* Bumped ASGE version to alpha3 [37b3f00_] (`#8685dc2 <https://github.com/HuxyUK/pyasge/commit/8685dc2b55956a00195b3126c709da2a75716f75>`__)

**Known Issues**

* Setting custom shaders can also effect previous render calls where
  the default shader was in use, resulting in both rendered quads
  using the same custom pixel shader. To resolve this use
  :code:`self.renderer.shader = None` when the default shader is desired.

.. _37b3f00: https://github.com/HuxyUK/ASGE/commit/37b3f00abd5e2bb8228aa937ffd8c97eb8c516fb

....

Version 1.0.0b2
---------------

:Date: April 26, 2021

* Added shader example (`#fb58306 <https://github.com/HuxyUK/pyasge/commit/fb5830612883233278b8f14c09f32540c7b581f9>`__)
* Added texture to property to sprite (`#1606af92 <https://github.com/HuxyUK/pyasge/commit/be46abcd6504ce82cffe1589ad5f8da57fc40b85>`__)
* Bumped ASGE version to alpha2 [34d4e67_] (`#cbf18b7 <https://github.com/HuxyUK/pyasge/commit/34d4e67341721fc7f7779ce2e5a2b035aff60f56>`__)

**Known Issues**

* Nvidia cards on Linux do not render correctly.

* Setting custom shaders can also effect previous render calls where
  the default shader was in use, resulting in both rendered quads
  using the same custom pixel shader. To resolve this use
  :code:`self.renderer.shader = None` when the default shader is desired.

.. _34d4e67: https://github.com/HuxyUK/ASGE/commit/4c061c7f3bcf0e49ce7aa2180e7c1a4c9abf87c8

....

Version 1.0.0b1
---------------

:Date: April 20, 2021

🎉 **Initial public release of PyASGE** 🎉

This is the first public release of PyASGE. It is considered beta quality.
From this point onwards any changes to v1 will be made with backwards
compatibility in mind as the API can be considered stable. Changes that break
the API will result in a major version bump.

**Known Issues**

* Nvidia cards on Linux do not render correctly.

* Setting custom shaders can also effect previous render calls where
  the default shader was in use, resulting in both rendered quads
  using the same custom pixel shader.
