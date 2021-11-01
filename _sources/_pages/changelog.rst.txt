ChangeLog
=========

Version 1.0.2
---------------

:Date: Oct 1, 2021

* Bumped ASGE version [435d35d_] (`#f7269f4 <https://github.com/HuxyUK/pyasge/commit/f7269f44e1e90ea75a5987b015d5cd2d4a881016>`__)

.. _435d35d: https://github.com/HuxyUK/ASGE/commit/435d35ddbe209e026bd991fcc001dd28c0b1c3c9

....

Version 1.0.1
---------------

:Date: Oct 17, 2021

* Expose read-only xy positional property (`#3ed23b3 <https://github.com/HuxyUK/pyasge/commit/3ed23b3f872738c3d55135a55f251dae2248e6b6>`__)
* Bumped ASGE version [85fd4e2_] (`#4688242 <https://github.com/HuxyUK/pyasge/commit/46882428d29b3c50b779599d34b86d65d00ebaca>`__)

.. _85fd4e2: https://github.com/HuxyUK/ASGE/commit/85fd4e205410653164d50bdb3b3b936fab0a0620

....

Version 1.0.0
---------------

:Date: May 14, 2021

🎉 **v1.0.0 release of PyASGE** 🎉

* Added property to access window's pixelbuffer resolution (`#5b6d043 <https://github.com/HuxyUK/pyasge/commit/5b6d043dcaa894cec672f130f416089fb9b5e01c>`__)
* Allow texture specific UV wrapping modes (`#b88c4f1 <https://github.com/HuxyUK/pyasge/commit/b88c4f17974ca505ea2d9ad11cd3fd94bb63d3ff>`__)
* Allow setting of default mag filter when scaling textures (`#e2e27e9 <https://github.com/HuxyUK/pyasge/commit/e2e27e9792b746e276f42292d09b7e676c21236f>`__)
* Bumped ASGE version [82aef53_] (`#2a0dca0 <https://github.com/HuxyUK/pyasge/commit/2a0dca09b273effac1732ca6c3f183a1d6445782>`__)

**Known Issues**

* None reported as this time

.. _82aef53: https://github.com/HuxyUK/ASGE/commit/82aef536e3939f9892974715f3e0513d3fe50108

....

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
