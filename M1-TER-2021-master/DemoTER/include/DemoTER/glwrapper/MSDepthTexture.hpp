#ifndef __MSDEPTHTEXTURE_HPP
#define	__MSDEPTHTEXTURE_HPP

#include "DemoTER/glwrapper/TexBuffer.hpp"

class MSDepthTexture: public TexBuffer {
	private:
		int samples;

	public:
		MSDepthTexture(int w, int h, int samples = 4);
		virtual void setSize(int w, int h) override;
		virtual void bind(int unit = 0) override;
};

#endif
