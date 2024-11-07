from flask import Flask, render_template, request, redirect, url_for

app = Flask(__name__)

# Sample data representing products and cart
products = [
    {'id': 1, 'name': 'Laptop', 'price': 1000},
    {'id': 2, 'name': 'Smartphone', 'price': 700},
    {'id': 3, 'name': 'Headphones', 'price': 200}
]
cart = []

# Home Page - Show products
@app.route('/')
def index():
    return render_template('index.html', products=products)

# Add Item to Cart
@app.route('/add/<int:product_id>', methods=['POST'])
def add_to_cart(product_id):
    product = next((item for item in products if item['id'] == product_id), None)
    if product:
        cart.append(product)
    return redirect(url_for('view_cart'))

# View Cart
@app.route('/cart')
def view_cart():
    total = sum(item['price'] for item in cart)
    return render_template('cart.html', cart=cart, total=total)

# Remove Item from Cart
@app.route('/remove/<int:product_id>')
def remove_from_cart(product_id):
    global cart
    cart = [item for item in cart if item['id'] != product_id]
    return redirect(url_for('view_cart'))

if __name__ == '__main__':
    app.run(debug=True)
