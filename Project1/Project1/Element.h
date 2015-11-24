#ifndef Element_H
#define Element_H


class Element {
public:
	Element() {
		texture = 5;
	}

	int getTexture() {
		return texture;
	}
	void setTexture(int texture) {
		this->texture = texture;
	}

private:
	int texture;
	int state = 0;
};

#endif