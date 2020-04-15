package ast;

import visitor.Visitor;

public class CharType implements Type {
	public void accept(Visitor v) {
		v.visit(this);
	}
}
