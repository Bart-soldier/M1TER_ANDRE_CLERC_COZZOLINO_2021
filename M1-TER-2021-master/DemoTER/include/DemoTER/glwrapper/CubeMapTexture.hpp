#ifndef __CUBEMAPTEXTURE_HPP
#define	__CUBEMAPTEXTURE_HPP

#include "DemoTER/glwrapper/TexBuffer.hpp"
#include <string>

/**
* Cette classe permet de repr�senter et de manipuler les textures sous frome de cartes d'environnements.
* C'est une classe abstraite. Elle h�rite de TexBuffer.
*/
class CubeMapTexture: public TexBuffer {
    public:
        struct Options {
            /**
            * Constructeur de la structure.
            * D�finit par d�faut le wrapping sur la coordonn�e s � GL_CLAMP_TO_EDGE, celui sur la coordonn�e t � GL_CLAMP_TO_EDGE,
            * celui sur la coordonn�e r � GL_CLAMP_TO_EDGE, le Min Filter GL_LINEAR et le Mag Filter � GL_LINEAR.
            */
            Options();

            GLenum wrapS;
            GLenum wrapT;
            GLenum wrapR;
            GLenum minFilter;
            GLenum magFilter;
        }; /**< Une structure pour les options. Ces derniers correspondent au param�tres de wrapping de texture sur s et t, et si
		   la pixel appliqu� sur la texture est plus petit ou plus grande que la texture m�me. */

        struct TexPaths {
            std::string top;
            std::string bot;
            std::string front;
            std::string back;
            std::string left;
            std::string right;
        }; /**< Une structure pour les chemins. Chaque chemin correspond � une partie de la carte d'environnement. */

        /**
        * Constructeur.
        * Cr�er une texture sous forme de carte d'environnement en fonction des param�tres fournis.
        * @param path Pointeur indiquant le chemin vers les textures composant la carte d'environnement.
        * @param params La correction gamma, par d�faut d�finie � faux.
        * @param options Les options de la texture, sinon ils correspondront aux valeurs du constructeur associ� par d�faut.
        */
        CubeMapTexture(TexPaths &paths, bool correctGamma = false, Options options = {});
        /**
        * Constructeur.
        * Cr�er une texture sous forme de carte d'environnement en fonction des param�tres fournis.
        * @param w La largeur de la carte d'environnement.
        * @param h La hauteur de la carte d'environnement.
        * @param params Le hdr, par d�faut d�finie � faux.
        * @param options Les options de la texture, sinon ils correspondront aux valeurs du constructeur associ� par d�faut.
        */
        CubeMapTexture(int w, int h, bool hdr = false, Options options = {});

        /**
        * Cette m�thode cr�er des MIP maps.
        */
        void createMips();

        /**
        * Permet de red�finir les options d'un texture.
        * @param options Les nouvelles options � d�finir.
        */
        void setOptions(Options options);
        /**
        * M�thode virtuelle pure.
        * Permet de rendre la classe abstraite.
        */
        virtual void bind(int unit = 0) override;

        virtual void setSize(int w, int h) override;
};

#endif
