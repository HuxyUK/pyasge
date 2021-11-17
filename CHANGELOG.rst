ChangeLog
=========

Version 1.1.0
---------------

:Date: Nov 17, 2021

* Bumped ASGE version [620596b_] (`#7b773c1 <https://github.com/HuxyUK/pyasge/commit/7b773c196b7fcc66c4ada3b8d7350518439ad080>`__)
* Added a new function to calculate Y bounds for text(`#bdb3a54 <https://github.com/HuxyUK/pyasge/commit/bdb3a546c6bb9951b3f0e0269b225638ecb1a2ac>`__)

**Notes**

* Attempts to fix the font bounds calculations again. However, existing fonts may now render smaller.
  The solution to this is to simply increase the imported size of the font.
* Mipmaps have been enabled for font rendering in ASGE

.. _620596b: https://github.com/HuxyUK/ASGE/commit/620596bce52b284d488fb887b7febb51ec559712
....

Version 1.0.3
---------------

:Date: Nov 16, 2021

* Bumped ASGE version [c9f1012_] (`#126fb00 <https://github.com/HuxyUK/pyasge/commit/e7f01fc0e2081c9a6c6fd16c4c9b9ba6b8be32f4>`__)
* Added a new logger that can be used for output to stdout(`#a27f39e <https://github.com/HuxyUK/pyasge/commit/a27f39ea98e52dd1c73723ac6538830e9f0426d5>`__)
* Introduction of Unity style fixed updates(`#a0aed58 <https://github.com/HuxyUK/pyasge/commit/a0aed5893f11cdbb9c6078ef705cb580ae902ddd>`__)
* Added field for MSAA support in Game Settings(`#cdb1768 <https://github.com/HuxyUK/pyasge/commit/cdb1768af7813fe63d30855a550085cb4f322445>`__)
* Support for MSAA Render Targets(`#4a5e736 <https://github.com/HuxyUK/pyasge/commit/4a5e7360ff6beef6bfdfb6c3988b3be182365264>`__)
* Updated documentation and examples

**Notes**

* Fixes bug with flipping sprites on the X axis
* Fixes bug with only DEBUG channel working for std out
* Removes sub-pixel clamping in the vertex shader, instead relying on the use of MSAA
* Introduces but does not force the use of a fixed update function. Update is now variable and can be considered a frame update

.. _c9f1012: https://github.com/HuxyUK/ASGE/commit/c9f10124722ea159521dcbde32efb3b3cb62385b
....

Version 1.0.3
---------------

:Date: Oct 1, 2021

* Bumped ASGE version [435d35d_] (`#f7269f4 <https://github.com/HuxyUK/pyasge/commit/f7269f44e1e90ea75a5987b015d5cd2d4a881016>`__)

.. _9d42f9b: https://github.com/HuxyUK/ASGE/commit/9d42f9bd075af0a86b2e3cc1f28a8eda04050422

....

Version 1.0.1
---------------

:Date: Oct 17, 2021


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
