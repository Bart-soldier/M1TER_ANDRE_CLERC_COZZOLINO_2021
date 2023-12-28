#ifndef __MERGESHADER_HPP
#define	__MERGESHADER_HPP

#include "DemoTER/glwrapper/Shader.hpp"

class MergeShader: public Shader {
	protected:
		virtual void fetchUniformLocations() override;

	public:
		MergeShader();
		/**
		* @param gamma, la correction à appliquer
		*/
		void setGamma(float gamma);
		/**
		* @param showBloom, choisi d'afficher seulement le bloom
		*/
		void setShowBloom(bool showBloom);

		enum {
			A_POSITION = 0,

			U_GAMMA = 0,
			U_BASE = 1,
			U_BLOOM = 2,
			U_SHOWBLOOM = 3,

			T_BASE = 0,
			T_BLOOM = 1,
		}; /**< Enum. A : Attributs, U : Uniform, T : Textures. */
};

#endif
