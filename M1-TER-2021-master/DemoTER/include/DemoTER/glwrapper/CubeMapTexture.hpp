#ifndef __CUBEMAPTEXTURE_HPP
#define	__CUBEMAPTEXTURE_HPP

#include "DemoTER/glwrapper/TexBuffer.hpp"
#include <string>

/**
* Cette classe permet de représenter et de manipuler les textures sous frome de cartes d'environnements.
* C'est une classe abstraite. Elle hérite de TexBuffer.
*/
class CubeMapTexture: public TexBuffer {
    public:
        struct Options {
            /**
            * Constructeur de la structure.
            * Définit par défaut le wrapping sur la coordonnée s à GL_CLAMP_TO_EDGE, celui sur la coordonnée t à GL_CLAMP_TO_EDGE,
            * celui sur la coordonnée r à GL_CLAMP_TO_EDGE, le Min Filter GL_LINEAR et le Mag Filter à GL_LINEAR.
            */
            Options();

            GLenum wrapS;
            GLenum wrapT;
            GLenum wrapR;
            GLenum minFilter;
            GLenum magFilter;
        }; /**< Une structure pour les options. Ces derniers correspondent au paramètres de wrapping de texture sur s et t, et si
		   la pixel appliqué sur la texture est plus petit ou plus grande que la texture même. */

        struct TexPaths {
            std::string top;
            std::string bot;
            std::string front;
            std::string back;
            std::string left;
            std::string right;
        }; /**< Une structure pour les chemins. Chaque chemin correspond à une partie de la carte d'environnement. */

        /**
        * Constructeur.
        * Créer une texture sous forme de carte d'environnement en fonction des paramètres fournis.
        * @param path Pointeur indiquant le chemin vers les textures composant la carte d'environnement.
        * @param params La correction gamma, par défaut définie à faux.
        * @param options Les options de la texture, sinon ils correspondront aux valeurs du constructeur associé par défaut.
        */
        CubeMapTexture(TexPaths &paths, bool correctGamma = false, Options options = {});
        /**
        * Constructeur.
        * Créer une texture sous forme de carte d'environnement en fonction des paramètres fournis.
        * @param w La largeur de la carte d'environnement.
        * @param h La hauteur de la carte d'environnement.
        * @param params Le hdr, par défaut définie à faux.
        * @param options Les options de la texture, sinon ils correspondront aux valeurs du constructeur associé par défaut.
        */
        CubeMapTexture(int w, int h, bool hdr = false, Options options = {});

        /**
        * Cette méthode créer des MIP maps.
        */
        void createMips();

        /**
        * Permet de redéfinir les options d'un texture.
        * @param options Les nouvelles options à définir.
        */
        void setOptions(Options options);
        /**
        * Méthode virtuelle pure.
        * Permet de rendre la classe abstraite.
        */
        virtual void bind(int unit = 0) override;

        virtual void setSize(int w, int h) override;
};

#endif
