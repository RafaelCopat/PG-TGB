#ifndef Element_H
#define Element_H


class Element {
public:
	Element() {
		texture = 5;
		tx = 0;
	}

	int getTexture() {
		return texture;
	}
	void setTexture(int texture) {
		this->texture = texture;
	}
	int getState() {
		return state;
	}
	void setState(int state) {
		this->state = state;
	}
	void charState() {
		if (state == 0) {
			tx = tx + 0.25;
			state = 1;
		}
		else if (state == 1) {
			tx = tx + 0.25;
			state = 2;
		}
		else if (state == 2) {
			tx = tx + 0.25;
			state = 3;
		}
		else if (state == 3) {
			tx = tx - 0.25;
			state = 4;
		}
		else if (state == 4) {
			tx = 0;
			state = 0;
		}
	}

	double getTx() {
		return tx;
	}

private:
	int texture;
	double tx;
	int state = 0;
};

#endif